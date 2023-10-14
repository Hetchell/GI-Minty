#include "InfinityEnergy.h"

namespace cheat {
	static bool LCAvatarCombat_IsEnergyMax(void* __this);

	InfinityEnergy::InfinityEnergy() {
		f_Enabled = config::getValue("functions:InfinityEnergy", "enabled", false);

		HookManager::install(app::LCAvatarCombat_IsEnergyMax, LCAvatarCombat_IsEnergyMax);
	}

	InfinityEnergy& InfinityEnergy::getInstance() {
		static InfinityEnergy instance;
		return instance;
	}

	void InfinityEnergy::GUI() {
		ConfigCheckbox(_("Infinity Energy"), f_Enabled);
		ImGui::SameLine();
		HelpMarker("Removes energy requirement for elemental bursts.\n"
			"(Energy bubble may appear incomplete but still usable)");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			infEnergyHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void InfinityEnergy::Outer() {
		if (infEnergyHotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void InfinityEnergy::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("InfinityEnergy"));
	}

	std::string InfinityEnergy::getModule() {
		return _("Player");
	}

	bool LCAvatarCombat_IsEnergyMax(void* __this) {
		auto& InfinityEnergy = InfinityEnergy::getInstance();

		if (InfinityEnergy.f_Enabled.getValue())
			return true;
		return CALL_ORIGIN(LCAvatarCombat_IsEnergyMax, __this);
	}
}
