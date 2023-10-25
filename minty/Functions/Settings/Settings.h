#pragma once

#include "../Function.h"
#include "../../Utils/GuiUtils.hpp"
#include "../../Config/ConfigManager.h"
#include "../../Themes/themes.hpp"
#include "../../Hotkeys/Hotkey.h"

namespace cheat {
	class Settings : public Function {
	public:
		ConfigField<bool> f_ShowFps;
		ConfigField<bool> f_ShowRpc;
		ConfigField<int> f_InitDelay;
		ConfigField<float> f_AnimationDuration;
		ConfigField<bool> f_ShowMenu;

		inline static Hotkey showMenuHotkey = Hotkey("ShowMenu", 0x7B);

		void GUI() override;
		void Outer() override;

		std::string getModule() override;

		static Settings& getInstance();

		Settings();
	};
}
