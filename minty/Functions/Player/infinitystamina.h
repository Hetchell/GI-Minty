#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class InfinityStamina : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey infStaminaHotkey = Hotkey("InfStamina");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static InfinityStamina& getInstance();

		InfinityStamina();
	};
}
