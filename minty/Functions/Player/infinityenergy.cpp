#include "infinityenergy.h"

static bool ifenergy;
static bool ifinit;
static bool LCAvatarCombat_IsEnergyMax(void* __this) {
	if (ifenergy)
		return true;
	return CALL_ORIGIN(LCAvatarCombat_IsEnergyMax, __this);
}

namespace il2fns {
	void Infinity__Energy() {
		while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinit) {
			HookManager::install(app::LCAvatarCombat_IsEnergyMax, LCAvatarCombat_IsEnergyMax); ifinit = true;
		}

		ifenergy = readBoolFuncStateFromJson("InfBurst");

		if (ImGui::Checkbox("Infinity Burst", &ifenergy)) {
			saveFuncStateToJson("InfBurst", ifenergy);
		}
		ImGui::SameLine();
		HelpMarker("Infinity burst energy. Energy indicator can be shown incorrect, but it is still working.");
	}
}