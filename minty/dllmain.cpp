#include "api/directx/D3D11Hook.hpp"
#include "il2cpp/il2cpp-init.hpp"
#include "api/lua/luahook.hpp"
#include "includes.h"
#include "utils/discordrpc/Discord.h"

#include "utils/ProtectionBypass.h"
#include "functions/Settings/Settings.h"

Discord* g_Discord;

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    LOG_INFO("Starting...");
    LOG_INFO("Initializing IL2CPP...");
    init_il2cpp();
    Sleep(5000);

    while (!FindWindowA("UnityWndClass", nullptr))
        Sleep(1000);

    ProtectionBypass::Init();

    auto& settings = cheat::Settings::getInstance();
    int initDelay = settings.f_InitDelay.getValue();

    if (settings.f_ShowRpc.getValue()) {
        g_Discord->Initialize();
        g_Discord->Update();
        LOG_INFO("Showing RPC...");
    }

    LOG_INFO("Initialized IL2CPP. Waiting %i seconds before starting DirectX...", initDelay / 1000);
    Sleep(initDelay);
    LOG_INFO("Waited, assuming that your game already opened. Opening menu...");

    try {
        GetPresent();
        DetourDirectXPresent();
    } catch (const std::exception& e) {
        LOG_ERROR("Unhandled exception in opening menu.");
    }
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(NULL, 0, &initLua, NULL, NULL, NULL));
        CreateThread(NULL, 0, &MainThread, NULL, NULL, NULL);
    }
    return TRUE;
}
