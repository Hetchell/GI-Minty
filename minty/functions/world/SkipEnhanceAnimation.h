#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class SkipEnhanceAnimation : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<bool> f_ShowLevelUp;

		inline static Hotkey skipAnimHotkey = Hotkey("SkipAnim");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static SkipEnhanceAnimation& getInstance();

		SkipEnhanceAnimation();
	};
}
