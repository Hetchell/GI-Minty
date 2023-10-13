#pragma once

#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../GUI/GuiDefinitions.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"

namespace cheat {
	class ProfileChanger : public FN {
	public:
		inline static bool ifUid;
		inline static std::string s_Uid;
		inline static Hotkey uidHotkey = Hotkey("Uid");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName = "Misc";

		static ProfileChanger& getInstance();

		ProfileChanger();

		std::string GetGroupName() override {
			return groupName;
		}
	};
}
