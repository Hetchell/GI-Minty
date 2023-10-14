#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class AutoTalk : public FN {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_TalkSpeed;

		inline static Hotkey dialogSkipHotkey = Hotkey("DialogSkip");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static AutoTalk& getInstance();

		AutoTalk();
	};
}
