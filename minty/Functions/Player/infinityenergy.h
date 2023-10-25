#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class InfinityEnergy : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey infEnergyHotkey = Hotkey("InfEnergy");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static InfinityEnergy& getInstance();

		InfinityEnergy();
	};
}
