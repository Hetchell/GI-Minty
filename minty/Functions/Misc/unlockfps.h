#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class UnlockFPS : public FN {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<int> f_Fps;

		inline static Hotkey unlockFPSHotkey = Hotkey("UnlockFPS");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static UnlockFPS& getInstance();

		UnlockFPS();
	};
}
