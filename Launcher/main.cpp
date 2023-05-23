#include <d3d11.h>
#include <Windows.h>
#pragma comment(lib, "d3d11.lib")
#include <sstream>
#include <iostream>
#include <filesystem>
#include <optional>
#include <fstream>
#include <commdlg.h>
#include "../minty/json/json.hpp"
//#include "D3D11Hook.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include <tchar.h>
#include "ImGui/imgui_internal.h"

#include "xorstr.hpp"

namespace fs = std::filesystem;

//std::ifstream f("cfg.json");
float ImLength(const ImVec2& lhs) {
    return sqrtf(lhs.x * lhs.x + lhs.y * lhs.y);
}

float GetContentRegionAvailWidth() {
    ImGuiWindow* window = ImGui::GetCurrentWindowRead();
    const ImVec2& contentSize = window->ContentSize;
    const float& scrollWidth = window->ScrollbarSizes.x;
    const float& availWidth = contentSize.x - scrollWidth - window->WindowPadding.x - window->WindowBorderSize * 2.0f;
    return availWidth > 0.0f ? availWidth : 0.0f;
}

float GetContentRegionAvailHeight() {
    ImGuiWindow* window = ImGui::GetCurrentWindowRead();
    const ImVec2& contentSize = window->ContentSize;
    const float& scrollHeight = window->ScrollbarSizes.y;
    const float& availHeight = contentSize.y - scrollHeight - window->WindowPadding.y - window->WindowBorderSize * 2.0f;
    return availHeight > 0.0f ? availHeight : 0.0f;
}

ImVec4 lerp(const ImVec4& a, const ImVec4& b, float t) {
    return ImVec4(
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t,
        a.w + (b.w - a.w) * t
    );
}

namespace ImGui {
    void drawGradientBackground(ImVec2 size, ImVec4 colorTop, ImVec4 colorBot) {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImVec2 p1 = p;
        ImVec2 p2 = ImVec2(p.x + size.x, p.y + size.y);

        draw_list->AddRectFilledMultiColor(p1, p2, ImColor(colorTop), ImColor(colorTop), ImColor(colorBot), ImColor(colorBot));
    }

    void drawRGradientBackground(const ImVec4& startColor, const ImVec4& endColor, float rotationAngleRadians, const ImVec2& startPos) {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        const ImVec2& gradientStartPos = startPos;
        const float& availWidth = GetContentRegionAvailWidth();
        const float& availHeight = GetContentRegionAvailHeight();
        const ImVec2& gradientEndPos = ImVec2(gradientStartPos.x + availWidth, gradientStartPos.y + availHeight);
        const ImVec2& gradientCenter = ImVec2((gradientStartPos.x + gradientEndPos.x) / 2.0f, (gradientStartPos.y + gradientEndPos.y) / 2.0f);
        const float& gradientLength = ImLength(gradientEndPos - gradientStartPos);
        const float& gradientAngle = atan2f(gradientEndPos.y - gradientStartPos.y, gradientEndPos.x - gradientStartPos.x);

        // Calculate the rotated start and end points
        const ImVec2& startPoint = ImVec2(gradientCenter.x + gradientLength / 2 * cosf(rotationAngleRadians + gradientAngle), gradientCenter.y + gradientLength / 2 * sinf(rotationAngleRadians + gradientAngle));
        const ImVec2& endPoint = ImVec2(gradientCenter.x + gradientLength / 2 * cosf(rotationAngleRadians - gradientAngle), gradientCenter.y + gradientLength / 2 * sinf(rotationAngleRadians - gradientAngle));

        ImU32 gradientColors[4] = { ImGui::GetColorU32(startColor), ImGui::GetColorU32(endColor), ImGui::GetColorU32(endColor), ImGui::GetColorU32(startColor) };

        // Calculate the transformed vertices of the rectangle
        ImVec2 vertices[4] = {
            startPoint,
            ImVec2(endPoint.x, startPoint.y),
            endPoint,
            ImVec2(startPoint.x, endPoint.y)
        };

        // Add the transformed rectangle to the draw list
        drawList->AddQuadFilled(vertices[0], vertices[1], vertices[2], vertices[3], gradientColors[3]);
    }
}

namespace util {
    //template<typename... Args>
    void log(const char* fmt, std::string args) {
        printf(xorstr_("[Minty] "));
        printf(fmt, args);
    }

    void logdialog(const char* fmt) {
        // LAMLMFNDPHJ.HAFGEFPIKFK is the Beebyte (more info: https://www.beebyte.co.uk/) obfuscated text for the game's error dialog.
        const char* errordialogformat = xorstr_("CS.LAMLMFNDPHJ.HAFGEFPIKFK(\"%s\",\"Minty\")");
        char errordialogtext[256];
        snprintf(errordialogtext, sizeof(errordialogtext), errordialogformat, fmt);
        //luahookfunc(errordialogtext);
        printf(errordialogtext);
    }
}

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
    if (!current_dir)
        return 0;

    auto dll_path = current_dir.value() / xorstr_("Minty.dll");
    if (!fs::is_regular_file(dll_path)) {
        printf(xorstr_("Minty.dll not found\n"));
        system("pause");
        return 0;
    }
    std::string exe_path;
    fs::path settings_path = fs::current_path() / xorstr_("minty");

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
            std::cout << xorstr_("Error: Unable to create config file.") << std::endl;
            return 1;
        }
    }

    settings_file >> cfg;

    auto settings = read_whole_file(settings_path);
    if (!settings) {
        printf(xorstr_("Failed reading config\n"));
        system("pause");
        return 0;
    }

    //std::string exe_path;
    //std::getline(std::stringstream(settings.value()), exe_path);
    std::cout << exe_path << std::endl;
    exe_path = cfg["exec_path"];
    std::cout << exe_path << std::endl;
    if (!fs::is_regular_file(exe_path)) {
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
        ofn.lpstrFilter = xorstr_("Executable Files (*.exe)\0*.exe\0All Files (*.*)\0*.*\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrTitle = xorstr_("Select Genshin Impact game executable");
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn)) {
            std::string(exe_path) = ofn.lpstrFile;
            std::ofstream settings_file(xorstr_("minty"), std::ios_base::out);
            if (settings_file.is_open()) {
                /*settings_file << exe_path << std::endl;
                settings_file.close();*/
                cfg["exec_path"] = exe_path;
                settings_file << cfg.dump(4) << std::endl;
                settings_file.close();
            } else {
                std::cout << xorstr_("Error: Unable to open settings file.") << std::endl;
                return 1;
            }
        } else {
            std::cout << xorstr_("Error: Unable to open file dialog.") << std::endl;
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

    return 0;
}


// Declare the external resources

// Function to load font from DLL resources
void LoadFontFromResources(HMODULE hModuleF, const wchar_t* fontName, float fontSize)
{
    //HMODULE hModuleF;
    // Find the resource handle within the DLL
    HRSRC hResource = FindResource(hModuleF, fontName, RT_RCDATA);
    if (!hResource)
    {
        // Resource not found
        //return nullptr;
    }

    // Load the resource data
    HGLOBAL hMemory = LoadResource(hModuleF, hResource);
    if (!hMemory)
    {
        // Failed to load resource
        //return nullptr;
    }

    // Get the resource data pointer and size
    LPVOID pData = LockResource(hMemory);
    DWORD dataSize = SizeofResource(hModuleF, hResource);

    // Create a memory buffer for the font data
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false; // We'll keep the memory until ImGui is shut down
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(pData, dataSize, fontSize, &fontConfig);

    // Clean up the resource handles
    UnlockResource(hMemory);
    FreeResource(hMemory);

    //return pFont;
}

/*
// Main code
//int WinMain(int, char**)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"Minty Launcher", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Minty Launcher", WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), 100, 100, 796, 500, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd)) {
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
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    HMODULE hModule = GetModuleHandle(nullptr);

    // Load font from resources
    ImFontConfig fontConfig;
    //ImFont* pFont;
    //ImFont* pFont = LoadFontFromResources(hModule, MAKEINTRESOURCEW(106), 18.0f);
    if (true)
    {
        // Set the font for ImGui to use
        //fontConfig.MergeMode = true;
        //ImGui::GetIO().Fonts->AddFont(&fontConfig);
    }
    LoadFontFromResources(hModule, MAKEINTRESOURCEW(108), 18.0f);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    int chosenGame = 0; // 0 - empty, 1 - gi, 2 - hsr
    // Main loop
    bool done = false;
    while (!done) {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            switch (msg.message) {
                case WM_QUIT:
                done=true;
            }
        }
        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0) {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;
            static float angleV = 0;
            ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            static bool open = true;
            //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            //ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
            ImGui::Begin("test window", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
            //ImGui::SliderFloat("slider", &angleV, 0.0f, 10.0f);
            if (chosenGame == 0)
                ImGui::drawGradientBackground(ImGui::GetContentRegionAvail(), ImVec4(181 / 255.0f, 181 / 255.0f, 181 / 255.0f, 1.0f), ImVec4(141 / 255.0f, 141 / 255.0f, 141 / 255.0f, 1.0f));
            if (chosenGame == 2)
                ImGui::drawGradientBackground(ImGui::GetContentRegionAvail(), ImVec4(35.0f / 255, 12.0f / 255, 67.5f / 255, 1.0f), ImVec4(181 / 255.0f, 181 / 255.0f, 181 / 255.0f, 1.0f));
            if (chosenGame == 1)
                ImGui::drawGradientBackground(ImGui::GetContentRegionAvail(), ImVec4(181 / 255.0f, 181 / 255.0f, 181 / 255.0f, 1.0f), ImVec4(127.5f / 255.0f, 103 / 255.0f, 17.5f / 255.0f, 1.0f));
            //ImGui::drawRotatedGradientBackground(ImGui::GetContentRegionAvail(), ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.0f, 1.0f, 0.0f, 1.0f), 80.0f);
            //ImGui::drawGradientBackground(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.0f, 0.0f, 1.0f, 1.0f), angleV, ImVec2(300, 300));

            ImGui::SetCursorPos(ImVec2(10, 320));
            ImGui::Button("Settings", ImVec2(250, 50));

            ImGui::SetCursorPos(ImVec2(10, 10));
            ImGui::BeginChild(4, ImVec2(250, 300), true);

            ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(270, 10));
            ImGui::BeginChild(5, ImVec2(500, 360), true);

            ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(10, 380));
            ImGui::BeginChild(7, ImVec2(760, 70), true);

            ImGui::SetCursorPos(ImVec2(10, 10));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(71.0f / 255, 24.0f / 255, 135.0f / 255, 1.0f));
            if (ImGui::Button("HSR", ImVec2(210, 50))) {
                chosenGame = 2;
            }
            ImGui::PopStyleColor();

            ImGui::SetCursorPos(ImVec2(230, 10));
            if (chosenGame == 0) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(181 / 255.0f, 181 / 255.0f, 181 / 255.0f, 1.0f));
                if (ImGui::Button("Start", ImVec2(305, 50))) {
                    //DoInjectStuff();
                }
                ImGui::PopStyleColor();
            }
            if (chosenGame == 1) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(255 / 255.0f, 206 / 255.0f, 35 / 255.0f, 1.0f));
                if (ImGui::Button("Start", ImVec2(305, 50))) {
                    //DoInjectStuff();
                }
                ImGui::PopStyleColor();
            }
            if (chosenGame == 2) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(71.0f / 255, 24.0f / 255, 135.0f / 255,  1.0f));
                if (ImGui::Button("Start", ImVec2(305, 50))) {
                    //DoInjectStuff();
                }
                ImGui::PopStyleColor();
            }

            ImGui::SetCursorPos(ImVec2(545, 10));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(255 / 255.0f, 206 / 255.0f, 35 / 255.0f, 1.0f));
            if (ImGui::Button("Anime Game", ImVec2(206, 50))) {
                chosenGame = 1;
            }
            ImGui::PopStyleColor();

            ImGui::EndChild();
            //ImGui::SetWindowSize({ 800.00f, 600.00f });

            /*
            draw->AddRect(ImVec2(pos.x + 270.f, pos.y + 88.f), ImVec2(pos.x + 278.f, pos.y + 110.f), ImColor(1.00f, 1.00f, 1.00f, 1.00f), 0.f, 256, 1.f);
            draw->AddRectFilled(ImVec2(pos.x + 62.f, pos.y + 8.f), ImVec2(pos.x + 790.f, pos.y + 590.f), ImColor(0.84f, 0.70f, 0.58f, 1.00f), 12.f, 240);
            draw->AddRect(ImVec2(pos.x + 76.f, pos.y + 17.f), ImVec2(pos.x + 332.f, pos.y + 383.f), ImColor(0.00f, 0.00f, 0.00f, 1.00f), 11.f, 16, 5.f);
            draw->AddRect(ImVec2(pos.x + 345.f, pos.y + 18.f), ImVec2(pos.x + 781.f, pos.y + 472.f), ImColor(0.00f, 0.00f, 0.00f, 1.00f), 11.f, 32, 5.f);
            draw->AddRectFilled(ImVec2(pos.x + 75.f, pos.y + 392.f ), ImVec2(pos.x + 332.f, pos.y + 473.f), ImColor(0.00f, 0.00f, 0.00f, 1.00f), 0.f, 256);
            draw->AddRectFilled(ImVec2(pos.x + 283.f, pos.y + 482.f), ImVec2(pos.x + 576.f, pos.y + 577.f), ImColor(0.00f, 0.00f, 0.00f, 1.00f), 0.f, 256);
            draw->AddRectFilled(ImVec2(pos.x + 76.f, pos.y + 484.f), ImVec2(pos.x + 273, pos.y + 574.f), ImColor(0.05f, 0.11f, 0.58f, 1.00f), 11.f, 64);
            if (ImGui::InvisibleButton("button1", ImVec2(196, 92))) {
                DoInjectStuff();
            }
            draw->AddRectFilled(ImVec2(pos.x + 583.f, pos.y + 483.f), ImVec2(pos.x + 779.f, pos.y + 575.f), ImColor(0.75f, 0.00f, 0.00f, 1.00f), 11.f, 128);
            //draw->AddText(Fonts::bahnschrift55, 55, pos + ImVec2{ 376.f, 498.f }, ImColor(1.00f, 1.00f, 1.00f, 1.00f), "Start");
            //draw->AddText(Fonts::bahnschrift41, 41, pos + ImVec2{ 124.f, 506.f }, ImColor(1.00f, 1.00f, 1.00f, 1.00f), "H: SR");
            //draw->AddText(Fonts::bahnschrift30, 30, pos + ImVec2{ 597.f, 516.f }, ImColor(1.00f, 1.00f, 1.00f, 1.00f), "Anime Game");
            //draw->AddText(39, pos + ImVec2{ 128.f, 410.f }, ImColor(1.00f, 1.00f, 1.00f, 1.00f), "Settings");
            * /

            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window) {
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
*/

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
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
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

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
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