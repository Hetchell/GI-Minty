#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <optional>
#include <fstream>
#include <commdlg.h>
#define _CRT_SECURE_NO_WARNINGS
#include "../minty/json/json.hpp"
//#include "D3D11Hook.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

//#include "../minty/gilua/util.h"
//#include "../minty/gilua/luahook.h"

namespace fs = std::filesystem;

//std::ifstream f("cfg.json");

namespace util
{
    //template<typename... Args>
    void log(const char* fmt, std::string args)
    {
        printf("[Minty] ");
        printf(fmt, args);
    }

    void logdialog(const char* fmt)
    {
        const char* errordialogformat = "CS.LAMLMFNDPHJ.HAFGEFPIKFK(\"%s\",\"Minty\")";
        char errordialogtext[256];
        snprintf(errordialogtext, sizeof(errordialogtext), errordialogformat, fmt);
        //luahookfunc(errordialogtext);
        printf(errordialogtext);
    }
}

bool InjectStandard(HANDLE hTarget, const char* dllpath)
{
    LPVOID loadlib = GetProcAddress(GetModuleHandle(L"kernel32"), "LoadLibraryA");

    LPVOID dllPathAddr = VirtualAllocEx(hTarget, NULL, strlen(dllpath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (dllPathAddr == NULL)
    {
        std::cout << "Failed allocating memory in the target process. GetLastError(): " << GetLastError() << "\n";
        return false;
    }

    if (!WriteProcessMemory(hTarget, dllPathAddr, dllpath, strlen(dllpath) + 1, NULL))
    {
        std::cout << "Failed writing to process. GetLastError(): " << GetLastError() << "\n";
        return false;
    }

    HANDLE hThread = CreateRemoteThread(hTarget, NULL, NULL, (LPTHREAD_START_ROUTINE)loadlib, dllPathAddr, NULL, NULL);
    if (hThread == NULL)
    {
        std::cout << "Failed to create a thread in the target process. GetLastError(): " << GetLastError() << "\n";
        return false;
    }

    WaitForSingleObject(hThread, INFINITE);

    DWORD exit_code = 0;
    GetExitCodeThread(hThread, &exit_code);

    VirtualFreeEx(hTarget, dllPathAddr, 0, MEM_RELEASE);
    CloseHandle(hThread);

    if (exit_code == 0)
    {
        std::cout << "LoadLibrary failed.\n";
        return false;
    }
    return true;
}

std::optional<std::string> read_whole_file(const fs::path& file)
try
{
    std::stringstream buf;
    std::ifstream ifs(file);
    if (!ifs.is_open())
        return std::nullopt;
    ifs.exceptions(std::ios::failbit);
    buf << ifs.rdbuf();
    return buf.str();
}
catch (const std::ios::failure&)
{
    return std::nullopt;
}

std::optional<fs::path> this_dir()
{
    HMODULE mod = NULL;
    TCHAR path[MAX_PATH]{};
    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)&this_dir, &mod))
    {
        printf("GetModuleHandleEx failed (%i)\n", GetLastError());
        return std::nullopt;
    }

    if (!GetModuleFileName(mod, path, MAX_PATH))
    {
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

// Main code
//int WinMain(int, char**)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Minty Launcher", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        /*if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);*/

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;
        
            ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            static bool open = true;
            ImGui::Begin("test window", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);                       // Create a window called "Hello, world!" and append into it.

            if (ImGui::Button("Open Game")) {
                nlohmann::json cfg;


                auto current_dir = this_dir();
                if (!current_dir)
                    return 0;

                auto dll_path = current_dir.value() / "Minty.dll";
                if (!fs::is_regular_file(dll_path))
                {
                    printf("Minty.dll not found\n");
                    system("pause");
                    return 0;
                }
                std::string exe_path;
                fs::path settings_path = fs::current_path() / "minty";

                /*std::ifstream ifs("cfg.json");
                ifs >> cfg;*/

                //f >> cfg;
                std::ifstream settings_file(settings_path);
                // Check if the settings file exists
                if (!fs::exists(settings_path)) {
                    std::ofstream settings_file(settings_path);
                    if (settings_file.is_open()) {
                        // Write the executable path to the settings file
                        cfg["exec_path"] = exe_path;
                        settings_file << cfg.dump(4) << std::endl;
                        settings_file.close();
                    }
                    else {
                        std::cout << "Error: Unable to create config file." << std::endl;
                        return 1;
                    }
                }

                settings_file >> cfg;

                auto settings = read_whole_file(settings_path);
                if (!settings)
                {
                    printf("Failed reading config\n");
                    system("pause");
                    return 0;
                }

                //std::string exe_path;
                //std::getline(std::stringstream(settings.value()), exe_path);
                std::cout << exe_path << std::endl;
                exe_path = cfg["exec_path"];
                std::cout << exe_path << std::endl;
                if (!fs::is_regular_file(exe_path))
                {
                    std::cout << "File path in settings.exe invalid" << std::endl;
                    std::cout << "Please select your Game Executable" << std::endl;
                    /* printf("Target executable not found\n");
                     system("pause");*/
                    OPENFILENAMEA ofn{};
                    char szFile[260]{};
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.lpstrFile = szFile;
                    ofn.lpstrFile[0] = '\0';
                    ofn.hwndOwner = NULL;
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrFilter = "Executable Files (*.exe)\0*.exe\0All Files (*.*)\0*.*\0";
                    ofn.nFilterIndex = 1;
                    ofn.lpstrTitle = "Select Executable File";
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

                    if (GetOpenFileNameA(&ofn))
                    {
                        std::string(exe_path) = ofn.lpstrFile;
                        std::ofstream settings_file("minty", std::ios_base::out);
                        if (settings_file.is_open()) {
                            /*settings_file << exe_path << std::endl;
                            settings_file.close();*/
                            cfg["exec_path"] = exe_path;
                            settings_file << cfg.dump(4) << std::endl;
                            settings_file.close();
                        }
                        else {
                            std::cout << "Error: Unable to open settings file." << std::endl;
                            return 1;
                        }
                    }
                    else {
                        std::cout << "Error: Unable to open file dialog." << std::endl;
                        return 1;
                    }

                    /*GetPresent();
                    printValues();
                    detourDirectXPresent();*/
                    exe_path = cfg["exec_path"];
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
                //CreateProcessA(exe_path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &proc_info);

                InjectStandard(proc_info.hProcess, dll_path.string().c_str());
                ResumeThread(proc_info.hThread);
                CloseHandle(proc_info.hThread);
                CloseHandle(proc_info.hProcess);
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
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
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

//int main()
//{
//    nlohmann::json cfg;
//
//
//    auto current_dir = this_dir();
//    if (!current_dir)
//        return 0;
//
//    auto dll_path = current_dir.value() / "Minty.dll";
//    if (!fs::is_regular_file(dll_path))
//    {
//        printf("Minty.dll not found\n");
//        system("pause");
//        return 0;
//    }
//    std::string exe_path;
//    fs::path settings_path = fs::current_path() / "minty";
//
//    /*std::ifstream ifs("cfg.json");
//    ifs >> cfg;*/
//
//    //f >> cfg;
//    std::ifstream settings_file(settings_path);
//    // Check if the settings file exists
//    if (!fs::exists(settings_path)) {
//        std::ofstream settings_file(settings_path);
//        if (settings_file.is_open()) {
//            // Write the executable path to the settings file
//            cfg["exec_path"] = exe_path;
//            settings_file << cfg.dump(4) << std::endl;
//            settings_file.close();
//        }
//        else {
//            std::cout << "Error: Unable to create config file." << std::endl;
//            return 1;
//        }
//    }
//
//    settings_file >> cfg;
//
//    auto settings = read_whole_file(settings_path);
//    if (!settings)
//    {
//        printf("Failed reading config\n");
//        system("pause");
//        return 0;
//    }
//
//    //std::string exe_path;
//    //std::getline(std::stringstream(settings.value()), exe_path);
//    std::cout << exe_path << std::endl;
//    exe_path = cfg["exec_path"];
//    std::cout << exe_path << std::endl;
//    if (!fs::is_regular_file(exe_path))
//    {
//        std::cout << "File path in settings.exe invalid" << std::endl;
//        std::cout << "Please select your Game Executable" << std::endl;
//        /* printf("Target executable not found\n");
//         system("pause");*/
//        OPENFILENAMEA ofn{};
//        char szFile[260]{};
//        ZeroMemory(&ofn, sizeof(ofn));
//        ofn.lStructSize = sizeof(ofn);
//        ofn.lpstrFile = szFile;
//        ofn.lpstrFile[0] = '\0';
//        ofn.hwndOwner = NULL;
//        ofn.nMaxFile = sizeof(szFile);
//        ofn.lpstrFilter = "Executable Files (*.exe)\0*.exe\0All Files (*.*)\0*.*\0";
//        ofn.nFilterIndex = 1;
//        ofn.lpstrTitle = "Select Executable File";
//        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
//
//        if (GetOpenFileNameA(&ofn))
//        {
//            std::string(exe_path) = ofn.lpstrFile;
//            std::ofstream settings_file("minty", std::ios_base::out);
//            if (settings_file.is_open()) {
//                /*settings_file << exe_path << std::endl;
//                settings_file.close();*/
//                cfg["exec_path"] = exe_path;
//                settings_file << cfg.dump(4) << std::endl;
//                settings_file.close();
//            }
//            else {
//                std::cout << "Error: Unable to open settings file." << std::endl;
//                return 1;
//            }
//        }
//        else {
//            std::cout << "Error: Unable to open file dialog." << std::endl;
//            return 1;
//        }
//
//        /*GetPresent();
//        printValues();
//        detourDirectXPresent();*/
//        exe_path = cfg["exec_path"];
//        PROCESS_INFORMATION proc_info{};
//        STARTUPINFOA startup_info{};
//        CreateProcessA(exe_path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &proc_info);
//
//        InjectStandard(proc_info.hProcess, dll_path.string().c_str());
//        ResumeThread(proc_info.hThread);
//        CloseHandle(proc_info.hThread);
//        CloseHandle(proc_info.hProcess);
//        return 0;
//    }
//
//    PROCESS_INFORMATION proc_info{};
//    STARTUPINFOA startup_info{};
//    CreateProcessA(exe_path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &proc_info);
//    //CreateProcessA(exe_path.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &proc_info);
//
//    InjectStandard(proc_info.hProcess, dll_path.string().c_str());
//    ResumeThread(proc_info.hThread);
//    CloseHandle(proc_info.hThread);
//    CloseHandle(proc_info.hProcess);
//    return 0;
//}