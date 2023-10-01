#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class Godmode : public FN {
	public:
		inline static bool ifGodmode;

		inline static Hotkey godModeHotkey = Hotkey("Godmode");

		void GUI() override;
		void Outer() override;
		void Status() override;

		Godmode();
	};
}
