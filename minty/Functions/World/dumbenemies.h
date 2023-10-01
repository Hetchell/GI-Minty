#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class DumbEnemies : public FN {
	public:
		inline static bool ifDumbEnemies;

		inline static Hotkey dumbEnemiesHotkey = Hotkey("DumbEnemies");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName = "World";

		DumbEnemies();

		std::string GetGroupName() override {
			return groupName;
		}
	};
}