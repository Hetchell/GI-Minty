#pragma once

#include "../il2cpp-appdata.h"
#include "../HookManager.h"
#include "../il2cpp-types.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"


namespace cheat {
	class Peeking : public FN {
	public:
		inline static bool ifPeeking;
		inline static Hotkey peekingHotkey = Hotkey("Peeking");
		std::string groupName = _("Misc");

		void GUI() override;
		void Outer() override;
		void Status() override;

		Peeking();
	};
}
