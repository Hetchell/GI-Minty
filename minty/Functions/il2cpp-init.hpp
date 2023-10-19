#pragma once

#include <Windows.h>
#include <sstream>
#include <fstream>

#include "../Utils/Utils.hpp"
#include "../Json/json.hpp"

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

#define SELECT_VERSION(VERSION, OS_OFFSET, CN_OFFSET) (VERSION == GameVersion::GLOBAL ? OS_OFFSET : CN_OFFSET)

enum class GameVersion {
	NONE,
	GLOBAL,
	CHINA
};

GameVersion getGameVersion() {
	//std::string execPath = config::getValue("exec_path", "", "").getValue();
	std::ifstream config_file("minty.json");
	nlohmann::json config_json;
	config_file >> config_json;
	config_file.close();

	std::string execpath = config_json["exec_path"];

	if (execpath.find("GenshinImpact.exe") != std::string::npos) {
		return GameVersion::GLOBAL;
	}
	if (execpath.find("YuanShen.exe") != std::string::npos) {
		return GameVersion::CHINA;
	}
	return GameVersion::NONE;
}

uintptr_t baseAddress;
uintptr_t unityPlayerAddress;

VOID init_il2cpp() {
	auto gameVersion = getGameVersion();

	if (gameVersion != GameVersion::NONE)
		util::log(M_Info, "Detected %s version.", gameVersion == GameVersion::GLOBAL ? "GLOBAL" : "CHINA");
	else {
		util::log(M_Error, "Failed to detect any game version. If you sure that cheat has updated for current game version, and you downloaded the correct one.");
		system("pause");
		exit(0);
		return;
	}

	while (baseAddress == (uint64_t) nullptr) {
		static bool repeat = false;

		if (!repeat) {
			repeat = true;
			util::log(M_Warning, "UserAssembly is still null. waiting..");
		}

		Sleep(1000);
		baseAddress = (uint64_t) GetModuleHandleA("UserAssembly.dll");

		if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
			baseAddress = (uint64_t) GetModuleHandleA("UserAssembly.dll");
			unityPlayerAddress = (uint64_t) GetModuleHandleA("UnityPlayer.dll");
			util::log(M_Debug, "UserAssembly ptr: %p", baseAddress);
			util::log(M_Debug, "UnityPlayer ptr: %p", unityPlayerAddress);

			#define DO_API(a, b, r, n, p) n = (r (*) p)(baseAddress + SELECT_VERSION(gameVersion, a, b))
				#include "il2cpp-api-functions.h"
			#undef DO_API

			#define DO_APP_FUNC(a, b, r, n, p) n = (r (*) p)(baseAddress + SELECT_VERSION(gameVersion, a, b))
			#define DO_APP_FUNC_METHODINFO(a, b, n) n = (struct MethodInfo **)(baseAddress + SELECT_VERSION(gameVersion, a, b))
				#include "il2cpp-functions.h"
			#undef DO_APP_FUNC
			#undef DO_APP_FUNC_METHODINFO

			#define DO_TYPEDEF(a, b, n) n ## __TypeInfo = (n ## __Class**) (baseAddress + SELECT_VERSION(gameVersion, a, b))
				#include "il2cpp-types.h"
			#undef DO_TYPEDEF

			#define DO_UP_FUNC(a, b, r, n, p) n = (r (*) p)(unityPlayerAddress + SELECT_VERSION(gameVersion, a, b))
				#include "il2cpp-unityplayer-functions.h"
			#undef DO_UP_FUNC
		}
	}
}
