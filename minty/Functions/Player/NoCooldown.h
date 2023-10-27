#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class NoCooldown : public Function {
	public:
		ConfigField<bool> f_EnabledSkill;
		ConfigField<bool> f_EnabledBow;
		ConfigField<bool> f_EnabledSprint;

		Hotkey f_HotkeySkill;
		Hotkey f_HotkeyBow;
		Hotkey f_HotkeySprint;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static NoCooldown& getInstance();

		NoCooldown();
	};
}
