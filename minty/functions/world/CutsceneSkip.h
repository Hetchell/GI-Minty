#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class CutsceneSkip : public Function {
	public:
		ConfigField<bool> f_Enabled;

		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static CutsceneSkip& getInstance();

		CutsceneSkip();
	};
}
