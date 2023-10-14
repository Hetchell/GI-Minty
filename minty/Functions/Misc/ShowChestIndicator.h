#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class ShowChestIndicator : public FN {
	public:
		ConfigField<bool> f_Enabled;

		inline static Hotkey chestIndicHotkey = Hotkey("ChestIndic");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static ShowChestIndicator& getInstance();

		ShowChestIndicator();
	};
}
