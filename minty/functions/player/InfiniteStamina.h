#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class InfiniteStamina : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<bool> f_EnabledPacket;

		Hotkey f_Hotkey;

		bool OnPropertySet(app::PropType__Enum propType);

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static InfiniteStamina& getInstance();

		InfiniteStamina();
	};
}
