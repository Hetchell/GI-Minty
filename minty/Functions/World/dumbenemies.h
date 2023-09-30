#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../HookManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../ImGui/ImGui/imgui.h"
#include "../../Utils/GuiUtils.hpp"
#include "../../Config/ConfigManager.hpp"
#include "../il2cppUtils.h"
#include "../../Hotkeys/Hotkey.h"

namespace il2fns {
	inline Hotkey dumbEnemiesHotkey = Hotkey("DumbEnemies");
	void DumbEnemies();
}