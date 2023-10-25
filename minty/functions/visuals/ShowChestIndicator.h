#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class ShowChestIndicator : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey chestIndicHotkey = Hotkey("ChestIndic");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static ShowChestIndicator& getInstance();

		ShowChestIndicator();
	};
}
