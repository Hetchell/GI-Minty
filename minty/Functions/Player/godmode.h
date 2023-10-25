#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class GodMode : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey godModeHotkey = Hotkey("Godmode");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static GodMode& getInstance();

		GodMode();
	};
}
