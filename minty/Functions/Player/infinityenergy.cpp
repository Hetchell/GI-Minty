#include "infinityenergy.h"

namespace cheat {
	static bool LCAvatarCombat_IsEnergyMax(void* __this);

	InfinityEnergy::InfinityEnergy() {
		HookManager::install(app::LCAvatarCombat_IsEnergyMax, LCAvatarCombat_IsEnergyMax);
	}

	void InfinityEnergy::GUI() {
		ImGui::Checkbox(_("Infinity Burst"), &ifInfEnergy);
		if (ifInfEnergy) {
			ImGui::Indent();
			infEnergyHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void InfinityEnergy::Outer() {
		if (infEnergyHotkey.IsPressed()) {
			ifInfEnergy = !ifInfEnergy;
		}
	}

	void InfinityEnergy::Status() {
		if (ifInfEnergy) {
			ImGui::Text(_("InfBurst"));
		}
	}

	static bool LCAvatarCombat_IsEnergyMax(void* __this) {
		if (InfinityEnergy::ifInfEnergy)
			return true;
		return CALL_ORIGIN(LCAvatarCombat_IsEnergyMax, __this);
	}
}