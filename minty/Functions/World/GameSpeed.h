#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class GameSpeed : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_Speed;

		inline static Hotkey speedHackHotkey = Hotkey("Speedhack");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static GameSpeed& getInstance();

		GameSpeed();
	};
}
