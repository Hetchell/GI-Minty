#include "../includes.h"
#include "../IL2CPP/il2cpp-init.hpp"
#include "../DirectX/D3D11Hook.hpp"
//#include "../Lua/luahook.hpp"
#include "something.h"

DWORD WINAPI MainThread(LPVOID lpReserved) {
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	util::log(2, "Starting");

	GetPresent();
	DetourDirectXPresent();
	PrintValues();

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