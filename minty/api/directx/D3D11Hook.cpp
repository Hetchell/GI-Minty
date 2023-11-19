// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif

// Detours imports
#include "../../il2cpp/detours.h"

// DX11 imports
#include <D3D11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "detours.lib")

#include <Windows.h>

#include "../../includes.h"
#include "../imgui/ImGui/imgui_internal.h"
#include "../../gui/InitGui.h"

// D3X HOOK DEFINITIONS
typedef HRESULT(__fastcall* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
//typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
// Definition of WndProc Hook. Its here to avoid dragging dependencies on <windows.h> types.
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main D3D11 Objects
//ResizeBuffers oResizeBuffers;
ID3D11DeviceContext* pContext = NULL;
namespace { ID3D11Device* pDevice = NULL; }
ID3D11RenderTargetView* mainRenderTargetView;
static IDXGISwapChain* pSwapChain = NULL;
static WNDPROC OriginalWndProcHandler = nullptr;
HWND window = nullptr;
IDXGISwapChainPresent fnIDXGISwapChainPresent;

bool LoadTextureFromResources(LPCTSTR resource_name, LPCTSTR resource_type, ID3D11Device* pDevice, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height) {
	if (pDevice == nullptr)
		return false;

	HMODULE hModuleF = GetModuleHandleA("minty.dll");
	//HMODULE hModuleF;
	// Find the resource handle within the DLL
	HRSRC hResource = FindResource(hModuleF, resource_name, resource_type);
	if (!hResource) {
		// Resource not found
		return false;
	}

	// Load the resource data
	HGLOBAL hMemory = LoadResource(hModuleF, hResource);
	if (!hMemory) {
		// Failed to load resource
		return false;
	}

	// Get the resource data pointer and size
	LPVOID pData = LockResource(hMemory);
	DWORD dataSize = SizeofResource(hModuleF, hResource);

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = *out_width;
	desc.Height = *out_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource, sizeof(subResource));
	subResource.pSysMem = pData;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;

	ID3D11Texture2D* pTexture = nullptr;
	pDevice->CreateTexture2D(&desc, &subResource, &pTexture);
	if (pTexture == nullptr)
		return false;

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = desc.Width;
	*out_height = desc.Height;
	return true;
}

// Boolean
BOOL g_bInitialised = false;
bool g_PresentHooked = false;

LRESULT CALLBACK hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ImGuiIO& io = ImGui::GetIO();
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(hWnd, &mPos);
	ImGui::GetIO().MousePos.x = static_cast<float>(mPos.x);
	ImGui::GetIO().MousePos.y = static_cast<float>(mPos.y);

	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	auto& settings = cheat::Settings::getInstance();

	if (settings.f_ShowMenu) {
		if (!app::Cursor_get_visible(nullptr)) {
			app::Cursor_set_visible(true);
			app::Cursor_set_lockState(app::CursorLockMode__Enum::None);
		}
		return true;
	} else if (!app::Cursor_get_visible(nullptr)) {
		app::Cursor_set_visible(false);
		app::Cursor_set_lockState(app::CursorLockMode__Enum::Locked);
	}

	return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
}

HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext) {
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}

//HRESULT hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
//	if (mainRenderTargetView) {
//		pContext->OMSetRenderTargets(0, 0, 0);
//		mainRenderTargetView->Release();
//	}
//
//	HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
//
//	ID3D11Texture2D* pBuffer;
//	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
//	// Perform error handling here!
//
//	pDevice->CreateRenderTargetView(pBuffer, NULL, &mainRenderTargetView);
//	// Perform error handling here!
//	pBuffer->Release();
//
//	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
//
//	// Set up the viewport.
//	D3D11_VIEWPORT vp;
//	vp.Width = Width;
//	vp.Height = Height;
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = 0;
//	pContext->RSSetViewports(1, &vp);
//	return hr;
//}

HRESULT __fastcall hkPresent(IDXGISwapChain* pChain, UINT SyncInterval, UINT Flags) {
	if (!g_bInitialised) {
		g_PresentHooked = true;

		//LOG_DEBUG("DirectX Present Hook called by first time");

		if (FAILED(GetDeviceAndCtxFromSwapchain(pChain, &pDevice, &pContext)))
			return fnIDXGISwapChainPresent(pChain, SyncInterval, Flags);

		pSwapChain = pChain;
		DXGI_SWAP_CHAIN_DESC sd;
		pChain->GetDesc(&sd);
		window = sd.OutputWindow;

		gui::InitImGui(window, pDevice, pContext);

		//Set OriginalWndProcHandler to the Address of the Original WndProc function
		OriginalWndProcHandler = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)hWndProc);
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

	gui::Render();

	//// Load texture from resources
	//int imageWidth = 512;  // Specify the desired image width
	//int imageHeight = 512; // Specify the desired image height
	//ID3D11ShaderResourceView* textureSRV = nullptr;
	//if (LoadTextureFromResources(MAKEINTRESOURCE(103), LPCSTR("PNG"), pDevice, &textureSRV, &imageWidth, &imageHeight)) {
	//	// Draw the texture
	//	ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
	//	//ImGui::SetNextWindowPos(ImVec2(about.width / 2, about.height * 0.063f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	//	if (ImGui::Begin("Gato", nullptr, flags)) {
	//		ImGui::Image(textureSRV, ImVec2(static_cast<float>(imageWidth), static_cast<float>(imageHeight)));
	//		ImGui::End();
	//	}
	//	textureSRV->Release();
	//}
	//else {
	//	util::log(2, "loadtex err");
	//}

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return fnIDXGISwapChainPresent(pChain, SyncInterval, Flags);
}

void DetourDirectXPresent() {
	//LOG_DEBUG("Calling fnIDXGISwapChainPresent Detour");
	DetourTransactionBegin();
	//LOG_DEBUG("Detour Begin Transaction");
	DetourUpdateThread(GetCurrentThread());
	//LOG_DEBUG("Detour Update Thread");
	// Detours the original fnIDXGISwapChainPresent with our Present
	//LOG_DEBUG("DX11 Present Address: %s", util::get_ptr(fnIDXGISwapChainPresent));
	//LOG_DEBUG("HookBuf Address: %s", util::get_ptr(oResizeBuffers));
	DetourAttach(&(LPVOID&)fnIDXGISwapChainPresent, (PBYTE)hkPresent);
	//DetourAttach(&(LPVOID&)oResizeBuffers, (PBYTE)hkResizeBuffers);
	//LOG_DEBUG("DX11 Detour Attach");
	DetourTransactionCommit();
}

void PrintValues() {
	LOG_DEBUG("Present Address: %s", util::get_ptr(fnIDXGISwapChainPresent));
	LOG_DEBUG("ID3D11DeviceContext Address: %s", util::get_ptr(pContext));
	LOG_DEBUG("ID3D11Device Address: %s", util::get_ptr(pDevice));
	LOG_DEBUG("ID3D11RenderTargetView Address: %s", util::get_ptr(mainRenderTargetView));
	LOG_DEBUG("IDXGISwapChain Address: %s", util::get_ptr(pSwapChain));
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
		LOG_ERROR("Failed to hook Present with VT method.");
		return;
	}

	DWORD_PTR* pSwapChainVtable = NULL;
	pSwapChainVtable = (DWORD_PTR*)swapchain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	fnIDXGISwapChainPresent = (IDXGISwapChainPresent)(DWORD_PTR)pSwapChainVtable[8];
	//oResizeBuffers = (ResizeBuffers)(DWORD_PTR)pSwapChainVtable[13];
	g_PresentHooked = true;
}

void* SwapChain[18];
void* Device[40];
void* Context[108];
