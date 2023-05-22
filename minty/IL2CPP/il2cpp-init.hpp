#include <Windows.h>
#include "../Utils/Utils.hpp"
#include "../GUI/GuiDefinitions.h"

uintptr_t baseAddress = (uint64_t)GetModuleHandleA("UserAssembly.dll");
uintptr_t unityPlayerAddress = (uint64_t)GetModuleHandleA("UnityPlayer.dll");

// Define IL2CPP API function addresses
#define DO_API(a, r, n, p) r(*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

// Define function addresses
#define DO_APP_FUNC(a, r, n, p) r(*n) p
namespace app {
#include "../IL2CPP/il2cpp-types.h"
#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC

// Define UnityPlayer functions
#define DO_UP_FUNC(a, r, n, p) r(*n) p
namespace app {
#include "il2cpp-unityplayer-functions.h"
}
#undef DO_UP_FUNC

//#define DO_MD1_FUNC(a, r, n, p) r(*n) p
//namespace app
//{
//#include "mDumper-funcs.h"
//}
//#undef DO_MD1_FUNC

//#define DO_MD2_FUNC(a, r, n, p) r(*n) p
//namespace app
//{
//#include "mDumper-funcs.h"
//}
//#undef DO_MD2_FUNC
//
//#define DO_MD3_FUNC(a, r, n, p) r(*n) p
//namespace app
//{
//#include "mDumper-funcs.h"
//}
//#undef DO_MD3_FUNC
//
//#define DO_MD4_FUNC(a, r, n, p) r(*n) p
//namespace app
//{
//#include "mDumper-funcs.h"
//}
//#undef DO_MD4_FUNC

//// Helper function to convert Il2CppString to std::string
//std::string il2cppi_to_string(app::Il2CppString* str) {
//	std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
//	return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
//}
//
//template<typename... Args>
//VOID il2cpp_run(void(*il2FN)(Args... argsFN)) {
//	if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
//		try {
//			&il2FN(argsFN...);
//		}
//		catch (app::Il2CppExceptionWrapper ex) {
//			if (ex.ex->message)
//				util::log(2, "%s\n", il2cppi_to_string(ex.ex->message).c_str());
//			if (ex.ex->stack_trace)
//				util::log(2, "%s\n", il2cppi_to_string(ex.ex->stack_trace).c_str());
//		}
//	}
//}

VOID init_il2cpp() {
//#define DO_API(a, r, n, p) n = (r (*) p)(baseAddress + n ## _ptr)
	util::log(M_Info, "Initializing isle too see pipi");

	while (baseAddress == (uint64_t)nullptr) {

		static bool repeat = false;

		if(!repeat) {
			repeat = true;
			util::log(M_Warning, "UA is still very not real. wawiting..");
		}

		Sleep(1000);
		baseAddress = (uint64_t)GetModuleHandleA("UserAssembly.dll");
		if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
			util::log(M_Debug, "now ua ptr: %s; up ptr: %s", util::get_ptr(baseAddress), util::get_ptr(unityPlayerAddress));

		#define DO_API(a, r, n, p) n = (r (*) p)(baseAddress + a)
		#include "il2cpp-api-functions.h"
		#undef DO_API

		#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + a)
		#include "il2cpp-functions.h"
		#undef DO_APP_FUNC

		#define DO_UP_FUNC(a, r, n, p) n = (r (*) p)(unityPlayerAddress + a)
		#include "il2cpp-unityplayer-functions.h"
		#undef DO_UP_FUNC
		is_il2cpp_hooked = true;

		}
	}

	util::log(M_Debug, "UserAssembly ptr: %s", util::get_ptr(baseAddress));
	util::log(M_Debug, "UnityPlayer ptr: %s", util::get_ptr(unityPlayerAddress));
}

VOID init_mD(int defind, int getnam, int getmed, int gentyp) {
	util::log(M_Debug, "Initializing isle too see pipi");

	while (baseAddress == (uint64_t)nullptr) {

		static bool repeat = false;

		if (!repeat) {
			repeat = true;
			util::log(M_Warning, "UA is still very not real. wawiting..");
		}

		Sleep(1000);
		baseAddress = (uint64_t)GetModuleHandleA("UserAssembly.dll");
		if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
			util::log(M_Debug, "now ua ptr: %p; up ptr: %p", baseAddress, unityPlayerAddress);

		//#define DO_MD1_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + defind)
		//#include "mDumper-funcs.h"
		//#undef DO_MD1_FUNC
		//	util::log(2, "defind defd: %s", util::int_to_hex(defind));

		//#define DO_MD2_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + getnam)
		//#include "mDumper-funcs.h"
		//#undef DO_MD2_FUNC
		//	util::log(2, "getnam defd: %s", util::int_to_hex(getnam));

		//#define DO_MD3_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + getmed)
		//#include "mDumper-funcs.h"
		//#undef DO_MD3_FUNC
		//	util::log(2, "getmed defd: %s", util::int_to_hex(getmed));

		//#define DO_MD4_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + gentyp)
		//#include "mDumper-funcs.h"
		//#undef DO_MD4_FUNC
		//	util::log(2, "gentyp defd: %s", util::int_to_hex(gentyp));
		}
	}
}
