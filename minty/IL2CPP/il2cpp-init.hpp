#include <Windows.h>

uintptr_t baseAddress = (UINT64)GetModuleHandle("UserAssembly.dll");
uintptr_t unityPlayerAddress = (UINT64)GetModuleHandle("UnityPlayer.dll");

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
#define DO_APP_FUNC(a, r, n, p) r(*n) p
namespace app {
#include "il2cpp-unityplayer-functions.h"
}
#undef DO_APP_FUNC

VOID init_il2cpp()
{
#define DO_API(a, r, n, p) n = (r (*) p)(baseAddress + n ## _ptr)
#include "il2cpp-api-functions.h"
#undef DO_API

#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + a)
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(unityPlayerAddress + a)
#include "il2cpp-unityplayer-functions.h"
#undef DO_APP_FUNC
	util::log(2, "isle too see pipi ready");
}
