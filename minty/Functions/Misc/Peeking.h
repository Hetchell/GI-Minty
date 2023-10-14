#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class Peeking : public FN {
	public:
		ConfigField<bool> f_Enabled;
		inline static Hotkey peekingHotkey = Hotkey("Peeking");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static Peeking& getInstance();

		Peeking();
	};
}
