#include "../includes.h"

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	util::log(2, "Starting", "");

	if (findDirect11SwapChain() != nullptr) {
		util::log(2, "Swpachain Found", "");
	}
	else {
		util::log(2, "Swapchain not found", "");
	}

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, &MainThread, NULL, NULL, NULL);
	}
	return TRUE;
}