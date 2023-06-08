#include "nocd.h"

static bool ifnocd;
static bool ifinit;
static bool ifbowinit;
static bool ifbow;

static bool LCAvatarCombat_OnSkillStart(app::LCAvatarCombat* __this, uint32_t skillID, float cdMultipler) {
	if (ifnocd)
	{
		cdMultipler = 0;
	}
	return CALL_ORIGIN(LCAvatarCombat_OnSkillStart, __this, skillID, cdMultipler);
}

static void ActorAbilityPlugin_AddDynamicFloatWithRange_Hook(app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minValue, float maxValue, bool forceDoAtRemote) {
	if (ifbow && il2cppi_to_string(key) == "_Enchanted_Time")
	{
		value = maxValue;
		__this->fields.nextValidAbilityID = 36;
	}
	CALL_ORIGIN(ActorAbilityPlugin_AddDynamicFloatWithRange_Hook, __this, key, value, minValue, maxValue, forceDoAtRemote);
}

namespace il2fns {
	void LCAvatarCombat_NoCD(bool value) {
		if (!ifinit)
			HookManager::install(app::LCAvatarCombat_OnSkillStart, LCAvatarCombat_OnSkillStart); ifinit = true;
		ifnocd = value;
	}

	void NoBowCD(bool value) {
		if (!ifbowinit)
			HookManager::install(app::MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, ActorAbilityPlugin_AddDynamicFloatWithRange_Hook); ifbowinit = true;
		ifbow = value;
	}
}