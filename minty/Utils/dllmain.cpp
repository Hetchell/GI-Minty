#include "../DirectX/D3D11Hook.hpp"
#include "../IL2CPP/il2cpp-init.hpp"
#include "../includes.h"
// #include "../Lua/luahook.hpp"
#include "../Lua/luahook.h"

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    util::log(2, "Starting");

    GetPresent();
    DetourDirectXPresent();
    // PrintValues(); // do we even need prntvalues, keep the comment here might be useful for later debug

    init_il2cpp();

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, &MainThread, NULL, NULL, NULL);
        CreateThread(NULL, 0, &initLua, NULL, NULL, NULL);
    }
    return TRUE;
}