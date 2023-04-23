#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

#include "../Utils/Log.hpp"
#include "../ImGui/ImGui/imgui.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// D3X HOOK DEFINITIONS
typedef HRESULT(__stdcall* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

// Definition of WndProc Hook. Its here to avoid dragging dependencies on <windows.h> types.
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static IDXGISwapChainPresent fnIDXGISwapChainPresent;
static ID3D11Device* pDevice = nullptr;

// static HRESULT __stdcall Present_Hook(IDXGISwapChain* pChain, const UINT SyncInterval, const UINT Flags)
// {
// 	static BOOL g_bInitialised = false;

// 	// Main D3D11 Objects
// 	static ID3D11DeviceContext* pContext = nullptr;
	
	
// 	if (!g_bInitialised)
// 	{
// 		auto result = (HRESULT)pChain->GetDevice(__uuidof(pDevice), reinterpret_cast<void**>(&pDevice));

// 		if (SUCCEEDED(result))
// 		{
// 			pDevice->GetImmediateContext(&pContext);

// 			DXGI_SWAP_CHAIN_DESC sd;
// 			pChain->GetDesc(&sd);

// 			backend::DX11Events::InitializeEvent(sd.OutputWindow, pDevice, pContext, pChain);

// 			g_bInitialised = true;
// 		}
// 	}

// 	// render function
// 	if (g_bInitialised)
// 		backend::DX11Events::RenderEvent(pContext);

// 	return CALL_ORIGIN(Present_Hook, pChain, SyncInterval, Flags);
// }

static IDXGISwapChainPresent findDirect11Present()
{
	WNDCLASSEX wc{ 0 };
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = TEXT("Class");

	if (!RegisterClassEx(&wc))
	{
		return nullptr;
	}

	HWND hWnd = CreateWindow(wc.lpszClassName, TEXT(""), WS_DISABLED, 0, 0, 0, 0, NULL, NULL, NULL, nullptr);

	IDXGISwapChain* pSwapChain;

	D3D_FEATURE_LEVEL featureLevel;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;  //((GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Main D3D11 Objects
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11Device* pDevice = nullptr;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP,     nullptr, 0, nullptr, 1, D3D11_SDK_VERSION, 
			&swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext)) &&
		FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, 
			&swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext)))
	{
		DestroyWindow(swapChainDesc.OutputWindow);
		UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

		return nullptr;
	}

	const DWORD_PTR* pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(pSwapChain);
	pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(pSwapChainVtable[0]);

	auto swapChainPresent = reinterpret_cast<IDXGISwapChainPresent>(pSwapChainVtable[8]);

	pDevice->Release();
	//pContext->Release();
	pSwapChain->Release();

	DestroyWindow(swapChainDesc.OutputWindow);
	UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

	return swapChainPresent;
}

void InitializeDX11Hooks() 
{
	util::log(3, "Starting DX11 Hook...","");
	fnIDXGISwapChainPresent = findDirect11Present();
	if (fnIDXGISwapChainPresent == nullptr)
	{
		util::log(1, "Failed to find \"Present\" for DX11","");
		return;
	}
	//LOG_DEBUG("SwapChain Present: %p", fnIDXGISwapChainPresent);
	util::log(3, "SwapChain Present Pointer: %p", fnIDXGISwapChainPresent);

	//HookManager::install(fnIDXGISwapChainPresent, Present_Hook);
	util::log(2, "DX11 Hook Initialized.","");
}