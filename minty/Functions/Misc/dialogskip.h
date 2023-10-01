#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class DialogSkip : public FN {
	public:
		inline static bool ifDialogSkip;
		inline static float fDialogSpeed = 1;

		inline static Hotkey dialogSkipHotkey = Hotkey("DialogSkip");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName = "Misc";

		DialogSkip();

		std::string GetGroupName() override {
			return groupName;
		}
	};
}
