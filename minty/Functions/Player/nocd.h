#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class NoCD : public FN {
	public:
		inline static bool ifNoSkillCD;
		inline static bool ifNoBowCD;
		inline static bool ifNoSprintCD;

		inline static Hotkey noSkillCDHotkey = Hotkey("NoSkillCD");
		inline static Hotkey noBowCDHotkey = Hotkey("NoBowCD");
		inline static Hotkey noSprintCDHotkey = Hotkey("NoSprintCD");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName = "Player";

		NoCD();

		std::string GetGroupName() override {
			return groupName;
		}
	};
}
