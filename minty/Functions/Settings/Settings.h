#pragma once

#include "../FunctionIncludes.h"
#include "../../themes/Themes.h"

namespace cheat {
	class Settings : public Function {
	public:
		ConfigField<bool> f_ShowFps;
		ConfigField<bool> f_ShowRpc;
		ConfigField<int> f_InitDelay;
		ConfigField<float> f_AnimationDuration;
		
		void GUI() override;
		void Outer() override;

		std::string getModule() override;

		static Settings& getInstance();

		Settings();
	};
}
