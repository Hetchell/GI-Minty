#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class CutsceneSkip : public FN {
	public:
		std::string groupName = _("Misc");
		inline static Hotkey skipCutsceneHotkey = Hotkey("CutsceneSkip");
		inline static bool ifSkipCutscene;

		void GUI() override;
		void Outer() override;
		void Status() override;

		CutsceneSkip();
	};
}
