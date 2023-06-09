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
	void DumbEnemies() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinit) {
            HookManager::install(app::MoleMole_VCMonsterAIController_TryDoSkill, VCMonsterAIController_TryDoSkill_Hook); ifinit = true;
        }

        ifdumb = readBoolFuncStateFromJson("DumbEnemy");

        if (ImGui::Checkbox("Dumb Enemies", &ifdumb)) {
            saveFuncStateToJson("DumbEnemy", ifdumb);
        }
        ImGui::SameLine();
        HelpMarker("Make enemies have the same level of intelligence as Congress.");
	}
}