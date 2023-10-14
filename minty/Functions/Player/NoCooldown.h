#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class NoCooldown : public FN {
	public:
		ConfigField<bool> f_EnabledSkill;
		ConfigField<bool> f_EnabledBow;
		ConfigField<bool> f_EnabledSprint;

		inline static Hotkey noSkillCDHotkey = Hotkey("NoSkillCD");
		inline static Hotkey noBowCDHotkey = Hotkey("NoBowCD");
		inline static Hotkey noSprintCDHotkey = Hotkey("NoSprintCD");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static NoCooldown& getInstance();

		NoCooldown();
	};
}
