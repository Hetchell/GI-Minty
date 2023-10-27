#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class OpenTeamImmediately : public Function {
	public:
		ConfigField<bool> f_Enabled;

		Hotkey f_Hotkey;

		void* InLevelPlayerProfilePageContext;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static OpenTeamImmediately& getInstance();

		OpenTeamImmediately();
	};
}
