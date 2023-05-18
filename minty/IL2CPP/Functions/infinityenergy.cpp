#include "infinityenergy.h"

static bool ifenergy;
static bool ifinit;
static bool LCAvatarCombat_IsEnergyMax(void* __this) {
	if (ifenergy)
		return true;

	return CALL_ORIGIN(LCAvatarCombat_IsEnergyMax, __this);
}

namespace il2fns {
	void Infinity__Energy(bool value) {
		if (!ifinit)
			HookManager::install(app::LCAvatarCombat_IsEnergyMax, LCAvatarCombat_IsEnergyMax); ifinit = true;
		ifenergy = value;
	}
}