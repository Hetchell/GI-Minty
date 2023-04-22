#include "D3d11Hook.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

static IDXGISwapChain* findDirect11SwapChain()
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

    IDXGISwapChain* pSwapChain = nullptr;
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

    if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 1, D3D11_SDK_VERSION,
        &swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext)) &&
        FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
            &swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext)))
    {
        DestroyWindow(swapChainDesc.OutputWindow);
        UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

        return nullptr;
    }

    pDevice->Release();
    pContext->Release();

    DestroyWindow(swapChainDesc.OutputWindow);
    UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

    return pSwapChain;
}
