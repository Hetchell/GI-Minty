#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

#include "pe.h"
#include "scanner.h"

#pragma warning(suppress : 4996)

extern "C" {
	#include "../lua/lauxlib.h"
	#include "../lua/lua.h"
	#include "../lua/lualib.h"
}

#include "../IL2CPP/HookManager.h"
#include "../Utils/LuaUtils.hpp"

int xluaL_loadbuffer_hook(lua_State* L, const char* chunk, size_t sz, const char* chunkname);
void exec(const std::string& compiled);
std::optional<std::string> compile(lua_State* L, const char* script);
void get_gi_L();
void luahookfunc(const char* charLuaScript);
DWORD WINAPI initLua(LPVOID lpReserved);