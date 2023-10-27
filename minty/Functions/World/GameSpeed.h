#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class GameSpeed : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_Speed;

		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static GameSpeed& getInstance();

		GameSpeed();
	};
}
