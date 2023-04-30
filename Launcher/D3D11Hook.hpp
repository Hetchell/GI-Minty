#include <Windows.h>

#include "../minty/GUI/MainGUI.h"
// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif

// Detours imports
#include "../minty/IL2CPP/detours.h"

// DX11 imports
#include <D3D11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "detours.lib")
#include "../minty/includes.h"
#include "../minty/ImGui/ImGui/imgui_internal.h"

// D3X HOOK DEFINITIONS
typedef HRESULT(__fastcall* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
// Definition of WndProc Hook. Its here to avoid dragging dependencies on <windows.h> types.
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main D3D11 Objects
ID3D11DeviceContext* pContext = NULL;
ID3D11Device* pDevice = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
static IDXGISwapChain* pSwapChain = NULL;
static WNDPROC OriginalWndProcHandler = nullptr;
HWND window = nullptr;
IDXGISwapChainPresent fnIDXGISwapChainPresent;

// Boolean
BOOL g_bInitialised = false;
bool g_ShowMenu = true;
bool g_PresentHooked = false;

LRESULT CALLBACK hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ImGuiIO& io = ImGui::GetIO();
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(window, &mPos);
	io.MousePos.x = static_cast<float>(mPos.x);
	io.MousePos.y = static_cast<float>(mPos.y);

	if (g_ShowMenu) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
			// If ImGui handled the message, don't pass it on to the main window procedure
			return true;
		}

		// Allow closing the window when ImGui is open
		if (uMsg == WM_CLOSE) {
			g_ShowMenu = false;
		}

		// Allow resizing and moving the window when ImGui is open
		if (uMsg == WM_ENTERSIZEMOVE) {
			io.MouseDrawCursor = false;
		}
		if (uMsg == WM_EXITSIZEMOVE) {
			io.MouseDrawCursor = true;
		}
		
		if (uMsg == WM_SIZE) {
			if (pDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				ImGuiIO& io = ImGui::GetIO();
				io.DisplaySize = ImVec2((float)LOWORD(lParam), (float)HIWORD(lParam));
				io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
			}
		}
	}
	else {
		// Allow closing the window when ImGui is closed
		if (uMsg == WM_CLOSE) {
			DestroyWindow(hWnd);
			return 0;
		}
	}

	// Pass any unhandled messages to the original window procedure
	return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
}

// Declare a function pointer for the original ResizeBuffers function
typedef HRESULT(WINAPI* ResizeBuffersFn)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

// Declare a global variable to hold the original ResizeBuffers function pointer
ResizeBuffersFn OriginalResizeBuffersFn = nullptr;

// Declare a hook for the ResizeBuffers function
HRESULT WINAPI HookedResizeBuffersFn(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	// Call the original ResizeBuffers function
	HRESULT hr = OriginalResizeBuffersFn(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	// Handle ImGui resizing
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)Width, (float)Height);
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

	return hr;
}

// Hook the ResizeBuffers function
void HookResizeBuffers(IDXGISwapChain* pSwapChain) {
	// Get the address of the original ResizeBuffers function
	OriginalResizeBuffersFn = (ResizeBuffersFn)GetProcAddress(GetModuleHandleA("dxgi.dll"), "IDXGISwapChain_ResizeBuffers");

	// Create a trampoline function to call the hooked ResizeBuffers function
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)OriginalResizeBuffersFn, HookedResizeBuffersFn);
	DetourTransactionCommit();
}


HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext) {
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}

HRESULT __fastcall hkPresent(IDXGISwapChain* pChain, UINT SyncInterval, UINT Flags) {
	if (!g_bInitialised) {
		g_PresentHooked = true;
		util::log(3, "Present Hook called by first time", "");
		if (FAILED(GetDeviceAndCtxFromSwapchain(pChain, &pDevice, &pContext)))
			return fnIDXGISwapChainPresent(pChain, SyncInterval, Flags);
		pSwapChain = pChain;
		DXGI_SWAP_CHAIN_DESC sd;
		pChain->GetDesc(&sd);
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		window = sd.OutputWindow;

		//Set OriginalWndProcHandler to the Address of the Original WndProc function
		OriginalWndProcHandler = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)hWndProc);

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
		ImGui::GetIO().ImeWindowHandle = window;

		ID3D11Texture2D* pBackBuffer;

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Use the UNORM format to specify RGB88 color space
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;

		pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, &rtvDesc, &mainRenderTargetView);
		pBackBuffer->Release();

		g_bInitialised = true;
	}

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();

	ImGui::NewFrame();

	ImGui::Begin("WTF");
	ImGui::End();

	//ImGuiIO& io = ImGui::GetIO();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return fnIDXGISwapChainPresent(pChain, SyncInterval, Flags);
}

void detourDirectXPresent() {
	util::log(3, "Calling fnIDXGISwapChainPresent Detour", "");
	DetourTransactionBegin();
	util::log(3, "Detour Begin Transaction", "");
	DetourUpdateThread(GetCurrentThread());
	util::log(3, "Detour Update Thread", "");
	// Detours the original fnIDXGISwapChainPresent with our Present
	DetourAttach(&(LPVOID&)fnIDXGISwapChainPresent, (PBYTE)hkPresent);
	util::log(3, "Detour Attach", "");
	DetourTransactionCommit();
}

void printValues() {
	util::log(3, "ID3D11DeviceContext Address: %p", pContext);
	util::log(3, "ID3D11Device Address: %p", pDevice);
	util::log(3, "ID3D11RenderTargetView Address: %p", mainRenderTargetView);
	util::log(3, "IDXGISwapChain Address: %p", pSwapChain);
}

LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }

void GetPresent() {
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 2;
	sd.BufferDesc.Height = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	D3D_FEATURE_LEVEL FeatureLevelsRequested = D3D_FEATURE_LEVEL_11_0;
	UINT numFeatureLevelsRequested = 1;
	D3D_FEATURE_LEVEL FeatureLevelsSupported;
	HRESULT hr;
	IDXGISwapChain* swapchain = 0;
	ID3D11Device* dev = 0;
	ID3D11DeviceContext* devcon = 0;
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&FeatureLevelsRequested,
		numFeatureLevelsRequested,
		D3D11_SDK_VERSION,
		&sd,
		&swapchain,
		&dev,
		&FeatureLevelsSupported,
		&devcon))) {
		util::log(3, "Failed to hook Present with VT method.", "");
		return;
	}
	DWORD_PTR* pSwapChainVtable = NULL;
	pSwapChainVtable = (DWORD_PTR*)swapchain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	fnIDXGISwapChainPresent = (IDXGISwapChainPresent)(DWORD_PTR)pSwapChainVtable[8];
	g_PresentHooked = true;

	util::log(3, "Present Address: %p", fnIDXGISwapChainPresent);
	Sleep(2000);
}

void* SwapChain[18];
void* Device[40];
void* Context[108];