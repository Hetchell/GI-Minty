#include "luahook.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/ProtectionBypass.h"

#pragma comment(lib, "detours.lib")
#pragma comment(lib, "ntdll.lib")

// HANDLE mainluathread;
extern std::vector<std::string> lua_list;

namespace fs = std::filesystem;

lua_State* gi_L;
HMODULE xlua;
HANDLE main_thread;

uintptr_t g_xluaL_loadbuffer;
uintptr_t g_lua_pcall;

static bool is_hook_success = false;
static int last_ret_code;
const char* last_tolstr;

typedef int (*pcall_ftn)(lua_State* L, int nargs, int nresults, int errfunc);
typedef int (*loadbuffer_ftn)(lua_State*, const char*, size_t, const char*);

loadbuffer_ftn LoadBuffer;
// pfn_loadbuffer* pp_loadbuffer;
uintptr_t il2cpp_base = 0;

int xluaL_loadbuffer_hook(lua_State* L, const char* chunk, size_t sz, const char* chunkname) {
    gi_L = L;
    util::log(M_Info, "xluaL_loadbuffer_hook called. Lua ready!");
    is_hook_success = true;
    main_thread = OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());
    util::log(M_Info, "main_thread created; id: %i", GetCurrentThreadId());
    int i = CALL_ORIGIN(xluaL_loadbuffer_hook, L, chunk, sz, chunkname);
    HookManager::detach(xluaL_loadbuffer_hook);
    return i;
}

void exec(const std::string& compiled) {
    int ret = ((loadbuffer_ftn)g_xluaL_loadbuffer)(gi_L, compiled.c_str(), compiled.length(), "Minty");
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
        util::log(M_Error, "compilation failed: %s", lua_tolstring(L, 1, NULL));
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
    util::log(M_Info, "FOUND");

    il2cpp_base = (uintptr_t)ua;
    g_xluaL_loadbuffer = PatternScan("UserAssembly.dll", "48 83 EC 38 E9");
    g_lua_pcall = PatternScan("UserAssembly.dll", "48 83 EC 38 33 C0 48 89 44 24 ? 48 89 44 24 ? E8 ? ? ? ? 48 83 C4 38 C3");
    printf("xluaL_loadbuffer: %p, rva: %p\n", g_xluaL_loadbuffer, g_xluaL_loadbuffer - il2cpp_base);
    printf("lua_pcall: %p, rva: %p\n", g_lua_pcall, g_lua_pcall - il2cpp_base);

    HookManager::install((loadbuffer_ftn)g_xluaL_loadbuffer, xluaL_loadbuffer_hook);
    printf("Hooked xluaL_loadbuffer, org: at %p\n", HookManager::getOrigin(xluaL_loadbuffer_hook));

    while (!gi_L)
        Sleep(50);

    printf("L: %p\n", gi_L);
}

void luahookfunc(const char* charLuaScript) {
    auto compiled = compile(gi_L, charLuaScript);
    if (!compiled)
        return;
    auto copy = new std::string(compiled.value());
    auto execute = [](ULONG_PTR compiled) {
        auto str = (const std::string*)compiled;
        exec(*str);
        delete str;
    };
    QueueUserAPC(execute, main_thread, (ULONG_PTR)copy);
};

DWORD WINAPI initLua(LPVOID lpReserved) {
    auto gi_LL = luaL_newstate();

    util::log(M_Info, "Starting");

    while (!FindWindowA("UnityWndClass", nullptr)) Sleep(1000);

	ProtectionBypass::DisableVMP();
    get_gi_L();
    //Sleep(10000);

    //util::log(M_Info, "should call now!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    //luahookfunc("CS.MoleMole.ActorUtils.ShowMessage(\"Lua initialized!\")");
    while (true) {
        //if (!last_lua_string.empty()) {
        //    luahookfunc(last_lua_string.c_str());
        //    util::log(M_Info, "Lua executed from s.");
        //    last_lua_string.clear();
        //    util::log(M_Info, "Lua deleted from s.");
        //}
        //Sleep(100);
        ////util::log(M_Info, "checked");
    }
    return 0;
}