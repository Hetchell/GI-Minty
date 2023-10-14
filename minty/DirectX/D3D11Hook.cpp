#include "../GUI/MainGUI.h"
// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif

// Detours imports
#include "../Functions/detours.h"

// DX11 imports
#include <D3D11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "detours.lib")

#include <Windows.h>

#include "../includes.h"
#include "../ImGui/ImGui/imgui_internal.h"
#include "../GUI/GuiDefinitions.h"

//#include "../ImGui/ImGuiNotify/imgui_notify.h"

#include "../GUI/InitGui.hpp"

// D3X HOOK DEFINITIONS
typedef HRESULT(__fastcall* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
// Definition of WndProc Hook. Its here to avoid dragging dependencies on <windows.h> types.
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main D3D11 Objects
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
//bool g_ShowMenu = true; -> defined in GUIDefinitions
bool g_PresentHooked = false;

LRESULT CALLBACK hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (block_input) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) && ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard) {
			return true; // ImGui wants to capture input, so return true
		}
		else {
			return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam); // let the main app handle the input
		}
	}
	else {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
	}
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
		util::log(M_Debug, "DirectX Present Hook called by first time");
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
	//util::log(3, "Calling fnIDXGISwapChainPresent Detour");
	DetourTransactionBegin();
	//util::log(3, "Detour Begin Transaction");
	DetourUpdateThread(GetCurrentThread());
	//util::log(3, "Detour Update Thread");
	// Detours the original fnIDXGISwapChainPresent with our Present
	util::log(M_Debug, "DX11 Present Address: %s", util::get_ptr(fnIDXGISwapChainPresent));
	DetourAttach(&(LPVOID&)fnIDXGISwapChainPresent, (PBYTE)hkPresent);
	util::log(M_Debug, "DX11 Detour Attach");
	DetourTransactionCommit();
}

void PrintValues() {
	util::log(M_Debug, "Present Address: %s", util::get_ptr(fnIDXGISwapChainPresent));
	util::log(M_Debug, "ID3D11DeviceContext Address: %s", util::get_ptr(pContext));
	util::log(M_Debug, "ID3D11Device Address: %s", util::get_ptr(pDevice));
	util::log(M_Debug, "ID3D11RenderTargetView Address: %s", util::get_ptr(mainRenderTargetView));
	util::log(M_Debug, "IDXGISwapChain Address: %s", util::get_ptr(pSwapChain));
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
		util::log(M_Error, "Failed to hook Present with VT method.");
		return;
	}
	DWORD_PTR* pSwapChainVtable = NULL;
	pSwapChainVtable = (DWORD_PTR*)swapchain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	fnIDXGISwapChainPresent = (IDXGISwapChainPresent)(DWORD_PTR)pSwapChainVtable[8];
	g_PresentHooked = true;

	//Sleep(2000);
}

void* SwapChain[18];
void* Device[40];
void* Context[108];