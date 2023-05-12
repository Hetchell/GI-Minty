#include "infinityenergy.h"

static bool LCAvatarCombat_IsEnergyMaxOn(void* __this) {
	if (true)
		return true;

	return CALL_ORIGIN(LCAvatarCombat_IsEnergyMaxOn, __this);
}

static bool LCAvatarCombat_IsEnergyMaxOff(void* __this) {
	if (true)
		return false;

	return CALL_ORIGIN(LCAvatarCombat_IsEnergyMaxOff, __this);
}

namespace il2fns {
	void Infinity__Energy(bool value) {
		if (value)
			HookManager::install(app::LCAvatarCombat_IsEnergyMax, LCAvatarCombat_IsEnergyMaxOn);
		else
			HookManager::install(app::LCAvatarCombat_IsEnergyMax, LCAvatarCombat_IsEnergyMaxOff);
	}
}