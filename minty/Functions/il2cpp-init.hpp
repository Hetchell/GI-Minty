#pragma once

#include <Windows.h>
#include <sstream>
#include <fstream>

#include "../Utils/Utils.hpp"
//#include "../GUI/GuiDefinitions.h"
#include "../Json/json.hpp"

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

enum GAMEVER : int {
	GLOBAL = 1,
	CHINA = 2
};

GAMEVER CheckGameVer() {
	std::ifstream config_file("minty.json");
	nlohmann::json config_json;
	config_file >> config_json;
	config_file.close();

	std::string execpath = config_json["exec_path"];

	if (execpath.find("GenshinImpact.exe") != std::string::npos) {
		return GLOBAL;
	}
	if (execpath.find("YuanShen.exe") != std::string::npos) {
		return CHINA;
	}
}

VOID init_il2cpp() {
	auto gameVer = CheckGameVer();

	while (baseAddress == (uint64_t) nullptr) {
		static bool repeat = false;

		if (!repeat) {
			repeat = true;
			util::log(M_Warning, "UA is still very not real. wawiting..");
		}

		Sleep(1000);
		baseAddress = (uint64_t) GetModuleHandleA("UserAssembly.dll");

		if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
			baseAddress = (uint64_t) GetModuleHandleA("UserAssembly.dll");
			unityPlayerAddress = (uint64_t) GetModuleHandleA("UnityPlayer.dll");
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
				util::log(M_Info, "Defined CHINA game client.");
			}
		}
	}
}
