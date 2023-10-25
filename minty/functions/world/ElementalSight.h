#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class ElementalSight : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey hotkey = Hotkey("ElementalSight");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static ElementalSight& getInstance();

		ElementalSight();
	};
}
