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
	class DialogSkip : public FN {
	public:
		inline static bool ifDialogSkip;
		std::string groupName = _("World");
		inline static Hotkey dialogSkipHotkey = Hotkey("DialogSkip");
		static bool ifSkipDialog;
		static bool ifSkipCutscene;
		inline static float fDialogSpeed = 1;

		void GUI() override;
		void Outer() override;
		void Status() override;

		DialogSkip();
	};
}
