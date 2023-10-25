#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class OpenTeamImmediately : public Function {
	public:
		ConfigField<bool> f_Enabled;

		void* InLevelPlayerProfilePageContext;

		inline static Hotkey otiHotkey = Hotkey("OTI");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static OpenTeamImmediately& getInstance();

		OpenTeamImmediately();
	};
}
