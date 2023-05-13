#pragma once
#ifndef LUAHOOK_H
#define LUAHOOK_H
#include <Windows.h>
#define OFFET 0x265CFF0
#include <cstdio>
#include <cstdint>
#include <sstream>
#include <optional>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "pe.h"
#include "scanner.h"
#pragma warning(suppress : 4996)
extern "C" {
#include "../lua/lua.h"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"
}
#include "../Utils/LuaUtils.hpp"
#include "../Utils/Utils.hpp"
#include "../IL2CPP/HookManager.h"
//#include "luaHook.h"

#pragma comment(lib, "detours.lib")
#pragma comment(lib, "ntdll.lib")
namespace {
    typedef enum _SECTION_INFORMATION_CLASS {
        SectionBasicInformation,
        SectionImageInformation
    } SECTION_INFORMATION_CLASS, * PSECTION_INFORMATION_CLASS;
    EXTERN_C NTSTATUS __stdcall NtQuerySection(HANDLE SectionHandle, SECTION_INFORMATION_CLASS InformationClass, PVOID InformationBuffer, ULONG InformationBufferSize, PULONG ResultLength);
    EXTERN_C NTSTATUS __stdcall NtProtectVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PULONG  NumberOfBytesToProtect, ULONG NewAccessProtection, PULONG OldAccessProtection);

    void DisableVMP() {
        DWORD old;
        VirtualProtect(NtProtectVirtualMemory, 1, PAGE_EXECUTE_READWRITE, &old);
        *(uintptr_t*)NtProtectVirtualMemory = *(uintptr_t*)NtQuerySection & ~(0xFFui64 << 32) | (uintptr_t)(*(uint32_t*)((uintptr_t)NtQuerySection + 4) - 1) << 32;
        VirtualProtect(NtProtectVirtualMemory, 1, old, &old);
    }

    namespace fs = std::filesystem;
    lua_State* gi_L;
    HMODULE xlua;
    HANDLE main_thread;

    uintptr_t g_xluaL_loadbuffer;
    uintptr_t g_lua_pcall;
    lua_State* gi_LL;
    //auto gi_LL = luaL_newstate();
    static bool lua_is_hooked = false;
    static int last_ret_code;
    const char* last_tolstr;

    typedef int (*pcall_ftn) (lua_State*, int, int, int);
    typedef int (*loadbuffer_ftn) (lua_State*, const char*, size_t, const char*);
    extern loadbuffer_ftn LoadBuffer;
    extern uintptr_t il2cpp_base = 0;

    int xluaL_loadbuffer_hook(lua_State* L, const char* chunk, size_t sz, const char* chunkname) {
        if (!gi_L) {
            gi_L = L;
            util::log(4, "xluaL_loadbuffer_hook called. Lua ready!");
            lua_is_hooked = true;
            main_thread = OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());
        }
        return CALL_ORIGIN(xluaL_loadbuffer_hook, L, chunk, sz, chunkname);
    }

    void exec(const std::string& compiled) {
        int ret = ((loadbuffer_ftn)g_xluaL_loadbuffer)(gi_L, compiled.c_str(), compiled.length(), "GILua");
        if (ret != 0) {
            lua_pop(gi_L, 1);
            return;
        }

        ret = ((pcall_ftn)g_lua_pcall)(gi_L, 0, 0, 0);
        if (ret != 0) {
            lua_pop(gi_L, 1);
        }
    }

    std::optional<std::string> compile(lua_State* L, const char* script) {
        std::ostringstream compiled_script;

        auto writer = [](lua_State* gi_l, const void* p, size_t sz, void* ud) -> int {
            auto out = (std::ostringstream*)ud;
            out->write((const char*)p, sz);
            return 0;
        };

        auto ret = luaL_loadstring(L, script);
        last_ret_code = ret;
        last_tolstr = lua_tolstring(L, 1, NULL);

        if (ret != 0) {
            std::string result = std::to_string(ret);
            //util::log(1,"compilation failed(%i)", result); // i dont think we need the err code :skull
            //util::log(1,"%s", lua_tolstring(L, 1, NULL));
            util::log(4, "compilation failed: %s", lua_tolstring(L, 1, NULL));
            //util::logdialog(lua_tolstring(L, 1, NULL)); ---- look in util.h; kinda useful but idk how to realise it at loading or how to mek slep
            lua_pop(L, 1);
            return std::nullopt;
        }

        ret = lua_dump(L, writer, &compiled_script, 0);
        if (ret != 0) {
            return std::nullopt;
        }

        lua_pop(L, 1);
        return compiled_script.str();
    }

    void get_gi_L() {
        HMODULE ua = NULL;
        while ((ua = GetModuleHandleW(L"UserAssembly.dll")) == 0) {
            Sleep(50);
        }
        util::log(4, "FOUND");
        //pp_loadbuffer = scan_loadbuffer(ua);
        //printf("hook func addr: %p\n", xluaL_loadbuffer_hook);
        //*pp_loadbuffer = xluaL_loadbuffer_hook;

        il2cpp_base = (uintptr_t)ua;
        g_xluaL_loadbuffer = PatternScan("UserAssembly.dll", "48 83 EC 38 4D 63 C0 48 C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 83 C4 38 C3");
        g_lua_pcall = PatternScan("UserAssembly.dll", "48 83 EC 38 33 C0 48 89 44 24 ? 48 89 44 24 ? E8 ? ? ? ? 48 83 C4 38 C3");
        util::log(4, "xluaL_loadbuffer: %s, rva: %p\n", util::get_ptr(g_xluaL_loadbuffer), g_xluaL_loadbuffer - il2cpp_base);
        util::log(4, "lua_pcall: %p, rva: %p\n", util::get_ptr(g_lua_pcall), g_lua_pcall - il2cpp_base); //com bac to lator

        HookManager::install((loadbuffer_ftn)g_xluaL_loadbuffer, xluaL_loadbuffer_hook);
        util::log(4, "Hooked xluaL_loadbuffer, org: at %p\n", HookManager::getOrigin(xluaL_loadbuffer_hook));
        //kiero::bind(99, (void**)&LoadBuffer, xluaL_loadbuffer_hook);

        while (!gi_L)
            Sleep(50);

        //kiero::unbind(99);
        util::log(4, "L: %p\n", gi_L);

    }

    void lua_runstr(const char* charLuaScript) {

        std::optional<std::string> compiled = compile(gi_LL, charLuaScript);
        //if (!compiled)
        //    return;
        //auto copy = new std::string(compiled.value());
        //auto execute = [](ULONG_PTR compiled) {
        //    auto str = (const std::string*)compiled;
        //    exec(*str);
        //    delete str;
        //};
        //QueueUserAPC(execute, main_thread, (ULONG_PTR)copy);
    };

    DWORD initLua(LPVOID) {

        util::log(4, "Starting");

        while (!FindWindowA("UnityWndClass", nullptr))  Sleep(1000);

        DisableVMP();
        get_gi_L();
        return TRUE;
    }
}
#endif LUAHOOK_H