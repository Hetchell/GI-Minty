#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class MultiHit : public FN {
	public:
		inline static bool ifMultiHit;
		inline static bool ifOnepunch;

		inline static Hotkey multiHitHotkey;

		inline static int hitQuantity;

		void GUI() override;
		void Outer() override;
		void Status() override;

		MultiHit();
	};
}