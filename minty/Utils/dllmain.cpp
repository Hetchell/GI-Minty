#include "../includes.h"
#include "../IL2CPP/il2cpp-init.hpp"
#include "../DirectX/D3D11Hook.hpp"

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	util::log(2, "Starting", "");

	GetPresent();
	printValues();

	detourDirectXPresent();

	init_il2cpp();

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, &MainThread, NULL, NULL, NULL);
	}
	return TRUE;
}