#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Utils/GuiUtils.hpp"
#include "../HookManager.h"

namespace cheat {
	class UnlockFPS : public FN {
	public:
		inline static bool ifUnlockFPS;
		inline static bool ifSavingMode;
		inline static int i_FPS;
		std::string groupName = "Misc";

		inline static Hotkey unlockFPSHotkey = Hotkey("UnlockFPS");

		void GUI() override;
		void Outer() override;
		void Status() override;

		UnlockFPS();

		std::string GetGroupName() override {
			return groupName;
		}
	};
}