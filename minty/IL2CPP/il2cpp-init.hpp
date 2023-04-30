#include <Windows.h>
#include "../Utils/Log.hpp"

uintptr_t baseAddress = (uint64_t)GetModuleHandle("UserAssembly.dll");
uintptr_t unityPlayerAddress = (uint64_t)GetModuleHandle("UnityPlayer.dll");

// Define IL2CPP API function addresses
#define DO_API(a, r, n, p) r(*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

// Define function addresses
#define DO_APP_FUNC(a, r, n, p) r(*n) p
namespace app {
#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC

// Define UnityPlayer functions
#define DO_UP_FUNC(a, r, n, p) r(*n) p
namespace app {
#include "il2cpp-unityplayer-functions.h"
}
#undef DO_UP_FUNC

VOID init_il2cpp() {
//#define DO_API(a, r, n, p) n = (r (*) p)(baseAddress + n ## _ptr)
	util::log(2, "isle too see pipi ready; loading ptrs.");
	util::log(2, "ua ptr: %p; up ptr: %p", baseAddress, unityPlayerAddress);
	while (baseAddress == (uint64_t)nullptr) {

		static bool repeat = false;

		if(!repeat) {
			repeat = true;
			util::log(1, "UA is still very not real. wawiting..");
		}

		Sleep(1000);
		baseAddress = (uint64_t)GetModuleHandle("UserAssembly.dll");
		if (GetModuleHandle("UserAssembly.dll") != nullptr) {
			util::log(2, "now ua ptr: %p; up ptr: %p", baseAddress, unityPlayerAddress);

		#define DO_API(a, r, n, p) n = (r (*) p)(baseAddress + a)
		#include "il2cpp-api-functions.h"
		#undef DO_API

		#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + a)
		#include "il2cpp-functions.h"
		#undef DO_APP_FUNC

		#define DO_UP_FUNC(a, r, n, p) n = (r (*) p)(unityPlayerAddress + a)
		#include "il2cpp-unityplayer-functions.h"
		#undef DO_UP_FUNC

		}
	}
}
