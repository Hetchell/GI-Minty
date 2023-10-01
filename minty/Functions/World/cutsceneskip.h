#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../HookManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../ImGui/ImGui/imgui.h"
#include "../../Utils/GuiUtils.hpp"
#include "../../Config/ConfigManager.hpp"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"

namespace cheat {
	class CutsceneSkip : public FN {
	public:
		std::string groupName = _("World");
		inline static Hotkey unlockFPSHotkey = Hotkey("CutsceneSkip");
		static bool ifSkipCutscene;

		void GUI() override;
		void Outer() override;
		void Status() override;

		CutsceneSkip();
	};
}
