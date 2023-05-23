#include "../DirectX/D3D11Hook.hpp"
#include "../IL2CPP/il2cpp-init.hpp"
#include "../includes.h"
#include "TelemetryBlocker.h"
#include "../Lua/luahook.hpp"

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    util::log(M_Info, "Starting");

    TelemetryBlocker::BlockTelemetry();

    GetPresent();
    DetourDirectXPresent();
    // PrintValues(); // do we even need prntvalues, keep the comment here might be useful for later debug

    // while (!FindWindowA("UnityWndClass", nullptr))  Sleep(1000);
    // DisableVMP();
    // get_gi_L();
    // Sleep(10000);
    // luahookfunc("CS.MoleMole.ActorUtils.ShowMessage(\"12312312312312231212123\")");

    init_il2cpp();

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(NULL, 0, &initLua, NULL, NULL, NULL));
        CreateThread(NULL, 0, &MainThread, NULL, NULL, NULL);
    }
    return TRUE;
}