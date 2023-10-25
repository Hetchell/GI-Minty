#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class FovChanger : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_Fov;

		inline static Hotkey fovChangerHotkey = Hotkey("FovChanger");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static FovChanger& getInstance();

		FovChanger();
	};
}
