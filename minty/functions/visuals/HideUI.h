#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class HideUI : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey hotkey = Hotkey("HideUI");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static HideUI& getInstance();

		HideUI();
	};
}
