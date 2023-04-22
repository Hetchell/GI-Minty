#include "includes.h"
//#include "lua/funcs.h" --- CRYING RIP MY FAV LANGUAGE
//#include "gilua/luaHook.h" --- CRYING RIP MY FAV LANGUAGE
//#include "lua/luaHook.cpp" --- CRYING RIP MY FAV LANGUAGE
//#include "lua/funcs.hpp" --- CRYING RIP MY FAV LANGUAGE

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <ShObjIdl.h>
#include <ObjBase.h>

using namespace std;

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	// AllocConsole();
    // freopen("CONIN$", "r", stdin);
    // freopen("CONOUT$", "w", stdout);
    // freopen("CONOUT$", "w", stderr);

    // util::log(1,"cock","");
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		//CloseHandle(CreateThread(NULL, 0, &, NULL, NULL, NULL)); --- idk if it is required
		CreateThread(NULL, 0, &MainThread, NULL, NULL, NULL);
	}
	return TRUE;
}