#include <Windows.h>
#include "../Utils/Utils.hpp"
#include "../GUI/GuiDefinitions.h"
#include "../Json/json.hpp"
#include <sstream>
#include <fstream>

uintptr_t baseAddress;
uintptr_t unityPlayerAddress;

// Define IL2CPP API function addresses
#define DO_API(a, b, r, n, p) r(*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

// Define function addresses
#define DO_APP_FUNC(a, b, r, n, p) r(*n) p
#define DO_TYPEDEF(a, n) n ## __Class** n ## __TypeInfo
#define DO_APP_FUNC_METHODINFO(a, n) struct MethodInfo ** n
namespace app {
#include "il2cpp-types.h"
#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC
#undef DO_TYPEDEF
#undef DO_APP_FUNC_METHODINFO

// Define UnityPlayer functions
#define DO_UP_FUNC(a, b, r, n, p) r(*n) p
namespace app {
#include "il2cpp-unityplayer-functions.h"
}
#undef DO_UP_FUNC



/*
#define DO_MD1_FUNC(a, r, n, p) r(*n) p
namespace app
{
#include "mDumper-funcs.h"
}
#undef DO_MD1_FUNC

#define DO_MD2_FUNC(a, r, n, p) r(*n) p
namespace app
{
#include "mDumper-funcs.h"
}
#undef DO_MD2_FUNC

#define DO_MD3_FUNC(a, r, n, p) r(*n) p
namespace app
{
#include "mDumper-funcs.h"
}
#undef DO_MD3_FUNC

#define DO_MD4_FUNC(a, r, n, p) r(*n) p
namespace app
{
#include "mDumper-funcs.h"
}
#undef DO_MD4_FUNC

// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(app::Il2CppString* str) {
	std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
	return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
}

template<typename... Args>
VOID il2cpp_run(void(*il2FN)(Args... argsFN)) {
	if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
		try {
			&il2FN(argsFN...);
		}
		catch (app::Il2CppExceptionWrapper ex) {
			if (ex.ex->message)
				util::log(2, "%s\n", il2cppi_to_string(ex.ex->message).c_str());
			if (ex.ex->stack_trace)
				util::log(2, "%s\n", il2cppi_to_string(ex.ex->stack_trace).c_str());
		}
	}
}
*/

// bool is_il2cpp_hooked = false;

enum GAMEVER : int {
	GLOBAL = 1,
	CHINA = 2
};

GAMEVER CheckGameVer() {
	std::ifstream config_file("minty");
	nlohmann::json config_json;
	config_file >> config_json;
	config_file.close();

	static std::string execpath = config_json["exec_path"];

	if (execpath.find("GenshinImpact.exe") != std::string::npos) {
		return GLOBAL;
	}
	if (execpath.find("YuanShen.exe") != std::string::npos) {
		return CHINA;
	}
}

VOID init_il2cpp() {
//#define DO_API(a, r, n, p) n = (r (*) p)(baseAddress + n ## _ptr)
	util::log(M_Info, "Initializing isle too see pipi");
	auto gameVer = CheckGameVer();

	while (baseAddress == (uint64_t)nullptr) {

		static bool repeat = false;

		if(!repeat) {
			repeat = true;
			util::log(M_Warning, "UA is still very not real. wawiting..");
		}

		Sleep(1000);
		baseAddress = (uint64_t)GetModuleHandleA("UserAssembly.dll");
		if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
			baseAddress = (uint64_t)GetModuleHandleA("UserAssembly.dll");
			unityPlayerAddress = (uint64_t)GetModuleHandleA("UnityPlayer.dll");
			util::log(M_Debug, "UserAssembly ptr: %p", baseAddress);
			util::log(M_Debug, "UnityPlayer ptr: %p", unityPlayerAddress);

			if (gameVer == GAMEVER::GLOBAL) {
#define DO_API(a, b, r, n, p) n = (r (*) p)(baseAddress + a)
#include "il2cpp-api-functions.h"
#undef DO_API

#define DO_APP_FUNC(a, b, r, n, p) n = (r (*) p)(baseAddress + a)
#define DO_APP_FUNC_METHODINFO(a, b, n) n = (struct MethodInfo **)(baseAddress + a)
#include "il2cpp-functions.h"
#undef DO_APP_FUNC
#undef DO_APP_FUNC_METHODINFO

#define DO_TYPEDEF(a, b, n) n ## __TypeInfo = (n ## __Class**) (baseAddress + a)
#include "il2cpp-types.h"
#undef DO_TYPEDEF

#define DO_UP_FUNC(a, b, r, n, p) n = (r (*) p)(unityPlayerAddress + a)
#include "il2cpp-unityplayer-functions.h"
#undef DO_UP_FUNC
				util::log(M_Info, "Defined GLOBAL game client.");
			}
			else if (gameVer == GAMEVER::CHINA) {
#define DO_API(a, b, r, n, p) n = (r (*) p)(baseAddress + b)
#include "il2cpp-api-functions.h"
#undef DO_API

#define DO_APP_FUNC(a, b, r, n, p) n = (r (*) p)(baseAddress + b)
#define DO_APP_FUNC_METHODINFO(a, b, n) n = (struct MethodInfo **)(baseAddress + b)
#include "il2cpp-functions.h"
#undef DO_APP_FUNC
#undef DO_APP_FUNC_METHODINFO

#define DO_TYPEDEF(a, b, n) n ## __TypeInfo = (n ## __Class**) (baseAddress + b)
#include "il2cpp-types.h"
#undef DO_TYPEDEF

#define DO_UP_FUNC(a, b, r, n, p) n = (r (*) p)(unityPlayerAddress + b)
#include "il2cpp-unityplayer-functions.h"
#undef DO_UP_FUNC
				util::log(M_Info, "Defined GLOBAL game client.");
			}
		// is_il2cpp_hooked = true;

		}
	}
}
/*
VOID init_mD(int defind, int getnam, int getmed, int gentyp) {
	util::log(M_Debug, "Initializing isle too see pipi");

	while (baseAddress == (uint64_t)nullptr) {

		static bool repeat = false;

		if (!repeat) {
			repeat = true;
			util::log(M_Warning, "UA is still very not real. Waiting..");
		}

		Sleep(1000);
		baseAddress = (uint64_t)GetModuleHandleA("UserAssembly.dll");

		if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
			util::log(M_Debug, "now ua ptr: %p; up ptr: %p", baseAddress, unityPlayerAddress);
			/*
			#define DO_MD1_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + defind)
			#include "mDumper-funcs.h"
			#undef DO_MD1_FUNC
				util::log(2, "defind defd: %s", util::int_to_hex(defind));

			#define DO_MD2_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + getnam)
			#include "mDumper-funcs.h"
			#undef DO_MD2_FUNC
				util::log(2, "getnam defd: %s", util::int_to_hex(getnam));

			#define DO_MD3_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + getmed)
			#include "mDumper-funcs.h"
			#undef DO_MD3_FUNC
				util::log(2, "getmed defd: %s", util::int_to_hex(getmed));

			#define DO_MD4_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + gentyp)
			#include "mDumper-funcs.h"
			#undef DO_MD4_FUNC
				util::log(2, "gentyp defd: %s", util::int_to_hex(gentyp));
			
		}
	}
}*/
