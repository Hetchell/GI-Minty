#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include <ShObjIdl.h>
#include <ObjBase.h>

#include <d3d11.h>
#include <dxgi.h>
#include <Windows.h>

#include "api/imgui/ImGui/imgui.h"
#include "api/imgui/ImGui/imgui_impl_win32.h"
#include "api/imgui/ImGui/imgui_impl_dx11.h"
#include "api/imgui/TextEditor/TextEditor.h"

//#include "Themes/themes.hpp"
#include "utils/LuaUtils.h"
#include "utils/util.h"
#include "api/json/json.hpp"
//#include "Lua/luahook.h"

//#include "Games/lightsout.hpp"
//#include "Games/minesweeper.hpp"
//#include "Games/tictactoe.hpp"
//#include "Games/wordle.hpp"
#include "api/imgui/TextEditor/TextEditor.h"
//#include "ImGui/ImGuiNotify/imgui_notify.h"
//#include "ImGui/ImGuiNotify/tahoma.h"
//#include "../minty/Games/lightsout.hpp"
//#include "../minty/Games/minesweeper.hpp"
//#include "../minty/Games/tictactoe.hpp"
//#include "../minty/Games/wordle.hpp"
//#include "../minty/Lua/luahook.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
