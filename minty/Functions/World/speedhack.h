#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class Speedhack : public FN {
	public:
		inline static bool ifSpeedhack;
		inline static float f_Speedhack;

		inline static Hotkey speedHackHotkey = Hotkey("Speedhack");

		void GUI() override;
		void Outer() override;
		void Status() override;

		Speedhack();
	};
}