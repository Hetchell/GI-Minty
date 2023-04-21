#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "../minty/Utils/Log.h"
#include <ShObjIdl.h>
#include <ObjBase.h>
#include "../minty/Themes/themes.h"
#include "../minty/Utils/ExtraGuiFuncs.hpp"
#include "../minty/ImGui/TextEditor.h"
//#include "../minty/Games/lightsout.hpp"
//#include "../minty/Games/minesweeper.hpp"
//#include "../minty/Games/tictactoe.hpp"
//#include "../minty/Games/wordle.hpp"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;