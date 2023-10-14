#pragma once

#include "../Function.h"
#include "../../Utils/GuiUtils.hpp"
#include "../../Config/ConfigManager.h"
#include "../../Themes/themes.hpp"

namespace cheat {
	class Settings : public Function {
	public:
		ConfigField<bool> f_ShowFps;
		ConfigField<bool> f_ShowRpc;
		ConfigField<int> f_InitDelay;
		
		void GUI() override;
		void Outer() override;

		std::string getModule() override;

		static Settings& getInstance();

		Settings();
	};
}
