#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class InfStamina : public FN {
	public:
		inline static bool ifInfStamina;

		inline static Hotkey infStaminaHotkey = Hotkey("InfStamina");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName = "Player";

		InfStamina();

		std::string GetGroupName() override {
			return groupName;
		}
	};
}