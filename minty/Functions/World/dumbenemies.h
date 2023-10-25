#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class DumbEnemies : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey dumbEnemiesHotkey = Hotkey("DumbEnemies");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static DumbEnemies& getInstance();

		DumbEnemies();
	};
}