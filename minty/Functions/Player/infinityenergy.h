#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
	class InfinityEnergy : public FN {
	public:
		inline static bool ifInfEnergy;

		inline static Hotkey infEnergyHotkey = Hotkey("InfEnergy");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName = _("Player");

		InfinityEnergy();
	};
}