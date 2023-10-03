#include "../DirectX/D3D11Hook.hpp"
#include "../Functions/il2cpp-init.hpp"
#include "../Lua/luahook.hpp"
#include "../includes.h"
#include "DiscordRPC/Discord.h"
#include "ProtectionBypass.h"

Discord* g_Discord;

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    util::log(M_Info, "Starting...");

    std::ifstream config_file("minty.json");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    bool showrpc = config_json["general"]["showRPC"];
    int initde = config_json["general"]["initDelay"];

    if (showrpc) {
        g_Discord->Initialize();
        g_Discord->Update();
        util::log(M_Info, "Showing RPC...");
    }

    util::log(M_Info, "Initializing IL2CPP...");
    // Initialize all offsets.
    init_il2cpp();
    Sleep(5000);
    ProtectionBypass::Init();

    util::log(M_Info, "Initialized IL2CPP. Waiting %i seconds before starting DirectX...", initde / 1000);
    Sleep(initde);

    util::log(M_Info, "Waited, assuming that your game already opened. Opening menu...");

    try {
        GetPresent();
        DetourDirectXPresent();
    } catch (const std::exception& e) {
        util::log(M_Error, "Unhandled exception in opening menu. Please report this issue in our Discord server.");
        // util::log(M_Error, e);
    }

    // PrintValues(); // do we even need prntvalues, keep the comment here might be useful for later debug

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(NULL, 0, &initLua, NULL, NULL, NULL));
        CreateThread(NULL, 0, &MainThread, NULL, NULL, NULL);
    }
    return TRUE;
}