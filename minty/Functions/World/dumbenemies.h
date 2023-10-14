#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class DumbEnemies : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey dumbEnemiesHotkey = Hotkey("DumbEnemies");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static DumbEnemies& getInstance();

		DumbEnemies();
	};
}