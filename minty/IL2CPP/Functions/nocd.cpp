#include "nocd.h"

static bool ifnocd;
static bool ifinit;
static bool ifbowinit;
static bool ifbow;
static bool LCAvatarCombat_IsSkillInCD_1(app::LCAvatarCombat* __this, app::LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo) {
	if (ifnocd)
	{
		auto cdTimer = app::MoleMole_SafeFloat_get_Value(skillInfo->fields.cdTimer); // Timer start value in the game

		if (cdTimer > 1)
		{
			struct app::SafeFloat MyValueProtect = app::MoleMole_SafeFloat_set_Value(1 - 1.0f); // Subtract -1 from the current timer value
			skillInfo->fields.cdTimer = MyValueProtect;
		}
	}
	return CALL_ORIGIN(LCAvatarCombat_IsSkillInCD_1, __this, skillInfo);
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
			HookManager::install(app::MoleMole_LCAvatarCombat_IsSkillInCD_1, LCAvatarCombat_IsSkillInCD_1); ifinit = true;
		ifnocd = value;
	}

	void NoBowCD(bool value) {
		if (!ifbowinit)
			HookManager::install(app::MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, ActorAbilityPlugin_AddDynamicFloatWithRange_Hook);
		ifbow = value;
	}
}