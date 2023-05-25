#include "../DirectX/D3D11Hook.hpp"
#include "../IL2CPP/il2cpp-init.hpp"
#include "../includes.h"
#include "TelemetryBlocker.h"
#include "ProtectionBypass.h"
#include "../Lua/luahook.hpp"

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    util::log(M_Info, "Starting...");

    //TelemetryBlocker::BlockTelemetry();
    //util::log(M_Info, "Telemetry block done.");
    try
    {
        ProtectionBypass::Init();
    }
    catch (const std::exception& e)
    {
        util::log(M_Error, "Unhandled exception in closing anticheat. Please report this issue in our Discord server.");
        //util::log(M_Error, e); // TODO: figure out how to log things that are of the std::exception class
    }

    util::log(M_Info, "Initializing IL2CPP...");
    init_il2cpp();

    util::log(M_Info, "Initialized IL2CPP. Waiting 30 seconds before starting DirectX...");
    Sleep(30000);

    util::log(M_Info, "Waited, assuming that your game already opened. Opening menu...");

    try
    {
        GetPresent();
        DetourDirectXPresent();
    }
    catch (const std::exception& e)
    {
        util::log(M_Error, "Unhandled exception in opening menu. Please report this issue in our Discord server.");
        //util::log(M_Error, e);
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