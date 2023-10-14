#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class OpenTeamImmediately : public FN {
	public:
		ConfigField<bool> f_Enabled;

		void* InLevelPlayerProfilePageContext;

		inline static Hotkey otiHotkey = Hotkey("OTI");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static OpenTeamImmediately& getInstance();

		OpenTeamImmediately();
	};
}
