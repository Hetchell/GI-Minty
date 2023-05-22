#pragma once
#include <Windows.h>
#define OFFET 0x265CFF0
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
#include "../GUI/GuiDefinitions.h"
#include "../IL2CPP/HookManager.h"
#include "../Utils/LuaUtils.hpp"
#include "../Utils/Utils.hpp"

// #include "luaHook.h"

static bool is_lua_hooked = false;

#pragma comment(lib, "detours.lib")
#pragma comment(lib, "ntdll.lib")

namespace {
typedef enum _SECTION_INFORMATION_CLASS {
    SectionBasicInformation,
    SectionImageInformation
} SECTION_INFORMATION_CLASS,
    *PSECTION_INFORMATION_CLASS;
EXTERN_C NTSTATUS __stdcall NtQuerySection(HANDLE SectionHandle, SECTION_INFORMATION_CLASS InformationClass, PVOID InformationBuffer, ULONG InformationBufferSize, PULONG ResultLength);
EXTERN_C NTSTATUS __stdcall NtProtectVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PULONG NumberOfBytesToProtect, ULONG NewAccessProtection, PULONG OldAccessProtection);

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
auto gi_LL = luaL_newstate();
// static bool is_lua_hooked = false;
static int last_ret_code;
const char* last_tolstr;

// using pfn_loadbuffer = int (*)(lua_State*, const char*, size_t, const char*);
// using pfn_loadbufferx = int (*)(lua_State*, const char*, size_t, const char*, size_t);

typedef int (*pcall_ftn)(lua_State* L, int nargs, int nresults, int errfunc);
typedef int (*loadbuffer_ftn)(lua_State*, const char*, size_t, const char*);
loadbuffer_ftn LoadBuffer;
// pfn_loadbuffer* pp_loadbuffer;
uintptr_t il2cpp_base = 0;
/*
int xluaL_loadbuffer_hook(lua_State* L, const char* chunk, size_t sz, const char* chunkname)
{
    gi_L = L;
    util::log(2,"xluaL_loadbuffer_hook called. Lua ready!","");
    is_lua_hooked = true;
    util::logdialog("Succesfully hooked. Happy hacking!");
    main_thread = OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());
    xlua = GetModuleHandleW(L"xlua");
    auto org = GetProcAddress(xlua, "xluaL_loadbuffer");
    printf("\norg xluaL_loadbuffer: %p, rva: %p\n", org, (uintptr_t)org - (uintptr_t)GetModuleHandleW(L"UserAssembly.dll"));
    *pp_loadbuffer = (pfn_loadbuffer)org;

    return (*pp_loadbuffer)(L, chunk, sz, chunkname);
}*/

int xluaL_loadbuffer_hook(lua_State* L, const char* chunk, size_t sz, const char* chunkname) {
    if (!gi_L) {
        gi_L = L;
        util::log(M_Debug, "xluaL_loadbuffer_hook called. Lua ready!");
        is_lua_hooked = true;
        // util::logdialog("Succesfully hooked. Happy hacking!");
        main_thread = OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());
    }
    return CALL_ORIGIN(xluaL_loadbuffer_hook, L, chunk, sz, chunkname);
}

/*
int xluaL_loadbuffer_hook(lua_State* L, const char* chunk, size_t sz, const char* chunkname)
{
    if (!gi_L) {
        gi_L = L;
        util::log(2, "xluaL_loadbuffer_hook called. Lua ready!", "");
        is_lua_hooked = true;
        util::logdialog("Succesfully hooked. Happy hacking!");
        main_thread = OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());
    }
    return LoadBuffer(L, chunk, sz, chunkname);
}*/

// std::optional<std::string> read_whole_file(const fs::path& file)
// try
//{
//     std::stringstream buf;
//     std::ifstream ifs(file);
//     if (!ifs.is_open())
//         return std::nullopt;
//     ifs.exceptions(std::ios::failbit);
//     buf << ifs.rdbuf();
//     return buf.str();
// }
// catch (const std::ios::failure&)
//{
//     return std::nullopt;
// }

void exec(const std::string& compiled) {
    // static auto xlua_pcall = (pfn_pcall)GetProcAddress(xlua, "lua_pcall");
    // static auto xluaL_loadbuffer = (pfn_loadbuffer)GetProcAddress(xlua, "xluaL_loadbuffer");

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

// std::optional<fs::path> this_dir()
//{
//     HMODULE mod = NULL;
//     TCHAR path[MAX_PATH]{};
//     if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)&this_dir, &mod))
//     {
//         printf("GetModuleHandleEx failed (%i)\n", GetLastError());
//         return std::nullopt;
//     }
//
//     if (!GetModuleFileName(mod, path, MAX_PATH))
//     {
//         printf("GetModuleFileName failed (%i)\n", GetLastError());
//         return std::nullopt;
//     }
//
//     return fs::path(path).remove_filename();
// }

// std::optional<fs::path> get_scripts_folder()
//{
//
//     auto mod_dir = this_dir();
//     if (!mod_dir)
//         return std::nullopt;
//
//     auto scripts_path = mod_dir.value() / "Scripts";
//     if (fs::is_directory(scripts_path))
//         return scripts_path;
//
//     //util::log("Scripts folder not found\n");
//     return std::nullopt;
// }
/*
pfn_loadbuffer* scan_loadbuffer(HMODULE ua)
{
    util::log(2,"Hooking... Attention: if logs stops at this line - you should inject dll before loading into world.","");
    auto il2cpp = util::pe::get_section_by_name(ua, "il2cpp");
    if (il2cpp == NULL)
        il2cpp = util::pe::get_section_by_name(ua, ".text");
    printf("il2cpp: %p, rva: %p\n", (uintptr_t)il2cpp, (uintptr_t)il2cpp - (uintptr_t)ua);

    auto rdata = util::pe::get_section_by_name(ua, ".rdata");
    printf("rdata: %p, rva: %p\n", (uintptr_t)rdata, (uintptr_t)rdata - (uintptr_t)ua);

    auto str = util::scanner::find_pat((const uint8_t*)"xluaL_loadbuffer", "xxxxxxxxxxxxxxxx", (const uint8_t*)((uint64_t)ua + rdata->VirtualAddress), rdata->Misc.VirtualSize);
    auto ref = util::scanner::find_ref_relative(str, (const uint8_t*)((uint64_t)ua + il2cpp->VirtualAddress), il2cpp->Misc.VirtualSize, true);

    auto a = util::scanner::find_pat((const uint8_t*)"\xE8\x00\x00\x00\x00\x48", "x????x", ref, 0x100);
    printf("a: %p, rva: %p\n", (uintptr_t)a, (uintptr_t)a - (uintptr_t)ua);
    a += 8;
    auto off = *(uint32_t*)a;
    pfn_loadbuffer* ptr = (pfn_loadbuffer*)(a + off + 4);
    printf("ptr: %p, rva: %p\n", ptr, (uintptr_t)ptr - (uintptr_t)ua);
    //printf("*ptr: %p, rva: %p\n", *ptr, (uintptr_t)*ptr - (uintptr_t)ua);
    //printf("up: %p\n", (uintptr_t)GetModuleHandleW(L"UnityPlayer.dll"));
    //printf("xlua: %p\n", (uintptr_t)GetModuleHandleW(L"xlua.dll"));
    return ptr;
}
*/
std::optional<std::string> compile(lua_State* L, const char* script) {
    std::ostringstream compiled_script;

    auto writer = [](lua_State* L, const void* p, size_t sz, void* ud) -> int {
        auto out = (std::ostringstream*)ud;
        out->write((const char*)p, sz);
        return 0;
    };

    auto ret = luaL_loadstring(L, script);
    last_ret_code = ret;
    last_tolstr = lua_tolstring(L, 1, NULL);

    if (ret != 0) {
        std::string result = std::to_string(ret);
        // util::log(1,"compilation failed(%i)", result); // i dont think we need the err code :skull
        // util::log(1,"%s", lua_tolstring(L, 1, NULL));
        util::log(M_Error, "Lua compile failed: %s", lua_tolstring(L, 1, NULL));
        // util::logdialog(lua_tolstring(L, 1, NULL)); ---- look in util.h; kinda useful but idk how to realise it at loading or how to mek slep
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
    util::log(M_Debug, "UserAssembly for Lua Found");
    // pp_loadbuffer = scan_loadbuffer(ua);
    // printf("hook func addr: %p\n", xluaL_loadbuffer_hook);
    //*pp_loadbuffer = xluaL_loadbuffer_hook;

    il2cpp_base = (uintptr_t)ua;
    g_xluaL_loadbuffer = PatternScan("UserAssembly.dll", "48 83 EC 38 4D 63 C0 48 C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 83 C4 38 C3");
    g_lua_pcall = PatternScan("UserAssembly.dll", "48 83 EC 38 33 C0 48 89 44 24 ? 48 89 44 24 ? E8 ? ? ? ? 48 83 C4 38 C3");

    // printf("xluaL_loadbuffer: %p, rva: %p\n", g_xluaL_loadbuffer, g_xluaL_loadbuffer - il2cpp_base);

    util::log(M_Debug, "xluaL_loadbuffer: %s, rva: %s", util::get_ptr(g_xluaL_loadbuffer), util::get_ptr(g_xluaL_loadbuffer - il2cpp_base));

    // printf("lua_pcall: %p, rva: %p\n", g_lua_pcall, g_lua_pcall - il2cpp_base);

    util::log(M_Debug, "lua_pcall: %s, rva: %s", util::get_ptr(g_lua_pcall), util::get_ptr(g_lua_pcall - il2cpp_base));

    HookManager::install((loadbuffer_ftn)g_xluaL_loadbuffer, xluaL_loadbuffer_hook);
    // printf("Hooked xluaL_loadbuffer, org: at %p\n", HookManager::getOrigin(xluaL_loadbuffer_hook));
    util::log(M_Debug, "Hooked xluaL_loadbuffer, org: at %s", util::get_ptr(HookManager::getOrigin(xluaL_loadbuffer_hook)));
    // kiero::bind(99, (void**)&LoadBuffer, xluaL_loadbuffer_hook);
    is_lua_hooked = true;

    while (!gi_L)
        Sleep(50);

    // kiero::unbind(99);
    // printf("L: %p\n", gi_L);
    util::log(M_Debug, "L: %s", util::get_ptr(gi_L));
}

DWORD initLua(LPVOID) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    util::log(M_Debug, "Initializing Lua");
    // auto dir = get_scripts_folder();

    while (!FindWindowA("UnityWndClass", nullptr)) Sleep(1000);

    DisableVMP();
    get_gi_L();

    // auto state = luaL_newstate();

    //// rsapatch breaks input, restore input mode
    /* SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),
         ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
         ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE |
         ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT
     );*/
    return TRUE;
}
}  // namespace