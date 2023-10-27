#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class UnlockFPS : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<int> f_Fps;
		ConfigField<bool> f_EnabledLimit;
		ConfigField<int> f_FpsLimit;

		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static UnlockFPS& getInstance();

		UnlockFPS();
	};
}
