#include "dumbenemies.h"

static bool ifdumb;
static bool ifinit;

static void VCMonsterAIController_TryDoSkill_Hook(void* __this, uint32_t skillID)
{
	if (ifdumb)
		return;
	CALL_ORIGIN(VCMonsterAIController_TryDoSkill_Hook, __this, skillID);
}

namespace il2fns {
	void DumbEnemies(bool value) {
		if (!ifinit)
			HookManager::install(app::MoleMole_VCMonsterAIController_TryDoSkill, VCMonsterAIController_TryDoSkill_Hook); ifinit = true;
		ifdumb = value;
	}
}