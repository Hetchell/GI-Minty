#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class FovChanger : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_Fov;

		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static FovChanger& getInstance();

		FovChanger();
	};
}
