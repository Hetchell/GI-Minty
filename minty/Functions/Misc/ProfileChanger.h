#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class ProfileChanger : public Function {
	public:
		ConfigField<bool> f_EnabledUid;
		ConfigField<std::string> f_Uid;

		inline static Hotkey uidHotkey = Hotkey("Uid");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static ProfileChanger& getInstance();

		ProfileChanger();
	};
}
