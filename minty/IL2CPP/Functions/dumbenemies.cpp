#include "dumbenemies.h"
static bool ifValue;
static void VCMonsterAIController_TryDoSkill_HookOn(void* __this, uint32_t skillID)
{
	return;
}

static void VCMonsterAIController_TryDoSkill_HookOff(void* __this, uint32_t skillID)
{
	CALL_ORIGIN(VCMonsterAIController_TryDoSkill_HookOff, __this, skillID);
}

namespace il2fns {
	void DumbEnemies(bool value) {
		if (value) {
			if (ifValue) {
				HookManager::detach(VCMonsterAIController_TryDoSkill_HookOff);
				ifValue = false;
			}
			HookManager::install(app::MoleMole_VCMonsterAIController_TryDoSkill, VCMonsterAIController_TryDoSkill_HookOn);
		}
		else {
			HookManager::detach(VCMonsterAIController_TryDoSkill_HookOn);
			ifValue = true;
			HookManager::install(app::MoleMole_VCMonsterAIController_TryDoSkill, VCMonsterAIController_TryDoSkill_HookOff);
		}
	}
}