#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include <ShObjIdl.h>
#include <ObjBase.h>

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

#include "ImGui/ImGui/imgui.h"
#include "ImGui/ImGui/imgui_impl_win32.h"
#include "ImGui/ImGui/imgui_impl_dx11.h"
#include "ImGui/TextEditor/TextEditor.h"

#include "Themes/themes.h"
//#include "Utils/ExtraGuiFuncs.hpp"
#include "Utils/Log.hpp"

#include "Json/json.hpp"
#include "Directx/D3D11Hook.h"
#include "DirectX/D3D11Hook.cpp"
//#include "Json/prejson.hpp"
//#include "Games/lightsout.hpp"
//#include "Games/minesweeper.hpp"
//#include "Games/tictactoe.hpp"
//#include "Games/wordle.hpp"
//#include "Utils/ExtraGuiFuncs.hpp"
#include "ImGui/TextEditor/TextEditor.h"
//#include "../minty/Games/lightsout.hpp"
//#include "../minty/Games/minesweeper.hpp"
//#include "../minty/Games/tictactoe.hpp"
//#include "../minty/Games/wordle.hpp"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;