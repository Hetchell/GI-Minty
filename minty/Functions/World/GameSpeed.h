#pragma once

#include "../FunctionIncludes.h"

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
