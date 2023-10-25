#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <sstream>
#include <iostream>
#include <filesystem>
#include <optional>
#include <fstream>
#include <commdlg.h>
#include <tchar.h>

#include "../minty/api/json/json.hpp"

namespace fs = std::filesystem;

bool InjectStandard(HANDLE hTarget, const char* dllpath) {
    LPVOID loadlib = GetProcAddress(GetModuleHandle(L"kernel32"), "LoadLibraryA");
    LPVOID dllPathAddr = VirtualAllocEx(hTarget, NULL, strlen(dllpath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (dllPathAddr == NULL) {
        std::cout << "Failed allocating memory in the target process. GetLastError(): " << GetLastError() << "\n";
        return false;
    }

    if (!WriteProcessMemory(hTarget, dllPathAddr, dllpath, strlen(dllpath) + 1, NULL)) {
        std::cout << "Failed writing to process. GetLastError(): " << GetLastError() << "\n";
        return false;
    }

    HANDLE hThread = CreateRemoteThread(hTarget, NULL, NULL, (LPTHREAD_START_ROUTINE)loadlib, dllPathAddr, NULL, NULL);

    if (hThread == NULL) {
        std::cout << "Failed to create a thread in the target process. GetLastError(): " << GetLastError() << "\n";
        return false;
    }

    WaitForSingleObject(hThread, INFINITE);

    DWORD exit_code = 0;
    GetExitCodeThread(hThread, &exit_code);

    VirtualFreeEx(hTarget, dllPathAddr, 0, MEM_RELEASE);
    CloseHandle(hThread);

    if (exit_code == 0) {
        std::cout << "LoadLibrary failed with exit code 0.\n";
        return false;
    }
    return true;
}

std::optional<std::string> read_whole_file(const fs::path& file)
try {
    std::stringstream buf;
    std::ifstream ifs(file);

    if (!ifs.is_open())
        return std::nullopt;

    ifs.exceptions(std::ios::failbit);
    buf << ifs.rdbuf();
    return buf.str();
} catch (const std::ios::failure&) {
    return std::nullopt;
}

std::optional<fs::path> this_dir() {
    HMODULE mod = NULL;
    TCHAR path[MAX_PATH]{};

    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)&this_dir, &mod)) {
        printf("GetModuleHandleEx failed (%i)\n", GetLastError());
        return std::nullopt;
    }

    if (!GetModuleFileName(mod, path, MAX_PATH)) {
        printf("GetModuleFileName failed (%i)\n", GetLastError());
        return std::nullopt;
    }

    return fs::path(path).remove_filename();
}

// Data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main() {
    nlohmann::json cfg;
    auto current_dir = this_dir();
    auto dll_path = current_dir.value() / "minty.dll";

    if (!fs::is_regular_file(dll_path)) {
        printf("minty.dll not found\n");
        system("pause");
        return 0;
    }

    std::string exe_path;
    fs::path settings_path = fs::current_path() / "minty.json";
    std::ifstream settings_file(settings_path);

    if (!fs::exists(settings_path)) {
        std::ofstream settings_file(settings_path);

        if (settings_file.is_open()) {
            // Write the executable path to the settings file
            cfg["general"]["execPath"] = exe_path;

            settings_file << cfg.dump(4) << std::endl;
            exe_path = cfg["general"]["execPath"];
            if (!fs::is_regular_file(exe_path)) {
                std::cout << "File path in minty.json invalid" << std::endl;
                std::cout << "Please select your Game Executable" << std::endl;

                OPENFILENAMEA ofn{};
                char szFile[260]{};
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.hwndOwner = NULL;
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "Executable\0GenshinImpact.exe;YuanShen.exe";
                ofn.nFilterIndex = 1;
                ofn.lpstrTitle = "Select Genshin Impact game executable";
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

                if (GetOpenFileNameA(&ofn)) {
                    std::string(exe_path) = ofn.lpstrFile;
                    std::ofstream settings_file("minty.json", std::ios_base::out);

                    if (settings_file.is_open()) {
                        cfg["general"]["execPath"] = exe_path;
                        settings_file << cfg.dump(4) << std::endl;
                        settings_file.close();
                    } else {
                        std::cout << "Error: Unable to open settings file." << std::endl;
                        return 1;
                    }
                } else {
                    std::cout << "Error: Unable to open file dialog." << std::endl;
                    return 1;
                }

                exe_path = cfg["general"]["execPath"];
                PROCESS_INFORMATION proc_info{};
                STARTUPINFOA startup_info{};
                CreateProcessA(exe_path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &proc_info);

                InjectStandard(proc_info.hProcess, dll_path.string().c_str());
                ResumeThread(proc_info.hThread);
                CloseHandle(proc_info.hThread);
                CloseHandle(proc_info.hProcess);
                return 0;
            }
        } else {
            std::cout << "Error: Unable to create config file." << std::endl;
        }
    }

    settings_file >> cfg;

    if (!read_whole_file(settings_path))
        printf("Failed reading config\n");

    exe_path = cfg["general"]["execPath"];

    if (!fs::is_regular_file(exe_path)) {
        std::cout << "File path in minty.json invalid" << std::endl;
        std::cout << "Please select your Game Executable" << std::endl;

        OPENFILENAMEA ofn{};
        char szFile[260]{};
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.hwndOwner = NULL;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "Executable\0GenshinImpact.exe;YuanShen.exe";
        ofn.nFilterIndex = 1;
        ofn.lpstrTitle = "Select Genshin Impact game executable";
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn)) {
            std::string(exe_path) = ofn.lpstrFile;
            std::ofstream settings_file("minty.json", std::ios_base::out);

            if (settings_file.is_open()) {
                cfg["general"]["execPath"] = exe_path;
                settings_file << cfg.dump(4) << std::endl;
                settings_file.close();
            } else {
                std::cout << "Error: Unable to open settings file." << std::endl;
                return 1;
            }
        } else {
            std::cout << "Error: Unable to open file dialog." << std::endl;
            return 1;
        }

        exe_path = cfg["general"]["execPath"];
        PROCESS_INFORMATION proc_info{};
        STARTUPINFOA startup_info{};
        CreateProcessA(exe_path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &proc_info);

        InjectStandard(proc_info.hProcess, dll_path.string().c_str());
        ResumeThread(proc_info.hThread);
        CloseHandle(proc_info.hThread);
        CloseHandle(proc_info.hProcess);
        return 0;
    }

    PROCESS_INFORMATION proc_info{};
    STARTUPINFOA startup_info{};
    CreateProcessA(exe_path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &proc_info);

    InjectStandard(proc_info.hProcess, dll_path.string().c_str());
    ResumeThread(proc_info.hThread);
    CloseHandle(proc_info.hThread);
    CloseHandle(proc_info.hProcess);
    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd) {
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);

    // Try high-performance WARP software driver if hardware is not available.
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D() {
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget() {
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget() {
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}
