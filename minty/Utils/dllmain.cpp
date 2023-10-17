#include "../DirectX/D3D11Hook.hpp"
#include "../Functions/il2cpp-init.hpp"
#include "../Lua/luahook.hpp"
#include "../includes.h"
#include "DiscordRPC/Discord.h"

#include "ProtectionBypass.h"
#include "../Functions/Settings/Settings.h"

Discord* g_Discord;

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    util::log(M_Info, "Starting...");
    util::log(M_Info, "Initializing IL2CPP...");
    init_il2cpp();
    Sleep(5000);
    ProtectionBypass::Init();

    auto& Settings = cheat::Settings::getInstance();
    int initDelay = Settings.f_InitDelay.getValue();

    if (Settings.f_ShowRpc.getValue()) {
        g_Discord->Initialize();
        g_Discord->Update();
        util::log(M_Info, "Showing RPC...");
    }

    util::log(M_Info, "Initialized IL2CPP. Waiting %i seconds before starting DirectX...", initDelay / 1000);
    Sleep(initDelay);
    util::log(M_Info, "Waited, assuming that your game already opened. Opening menu...");

    try {
        GetPresent();
        DetourDirectXPresent();
    } catch (const std::exception& e) {
        util::log(M_Error, "Unhandled exception in opening menu. Please report this issue in our Discord server.");
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
