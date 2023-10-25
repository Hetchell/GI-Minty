#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class NoFog : public Function {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey hotkey = Hotkey("NoFog");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static NoFog& getInstance();

		NoFog();
	};
}
