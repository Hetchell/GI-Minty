#include "InfiniteEnergy.h"

namespace cheat {
	static bool LCAvatarCombat_IsEnergyMax(void* __this);

	InfiniteEnergy::InfiniteEnergy() {
		f_Enabled = config::getValue("functions:InfiniteEnergy", "enabled", false);
		f_Hotkey = Hotkey("functions:InfiniteEnergy");

		HookManager::install(app::MoleMole_LCAvatarCombat_IsEnergyMax, LCAvatarCombat_IsEnergyMax);
	}

	InfiniteEnergy& InfiniteEnergy::getInstance() {
		static InfiniteEnergy instance;
		return instance;
	}

	void InfiniteEnergy::GUI() {
		ConfigCheckbox(_("Infinite Energy"), f_Enabled, "Removes energy requirement for elemental bursts.\n"
			"(Energy bubble may appear incomplete but still usable)");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void InfiniteEnergy::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void InfiniteEnergy::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("Infinite Energy"));
	}

	std::string InfiniteEnergy::getModule() {
		return _("Player");
	}

	bool LCAvatarCombat_IsEnergyMax(void* __this) {
		auto& infiniteEnergy = InfiniteEnergy::getInstance();

		if (infiniteEnergy.f_Enabled.getValue())
			return true;
		return CALL_ORIGIN(LCAvatarCombat_IsEnergyMax, __this);
	}
}
