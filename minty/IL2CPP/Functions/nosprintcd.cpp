#include "nosprintcd.h"

static bool ifnosprintcd;
static bool ifinit;
static bool HumanoidMoveFSM_CheckSprintCooldown_Hook(void* __this)
{
	if (ifnosprintcd)
		return true;
	return CALL_ORIGIN(HumanoidMoveFSM_CheckSprintCooldown_Hook, __this);
}

namespace il2fns {
	void NoSprintCD() {

		while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinit)
		{
			HookManager::install(app::MoleMole_HumanoidMoveFSM_CheckSprintCooldown, HumanoidMoveFSM_CheckSprintCooldown_Hook); ifinit = true;
		}

		ifnosprintcd = readBoolFuncStateFromJson("SprintCD");

		if (ImGui::Checkbox("Disable sprint CD", &ifnosprintcd)) {


			saveFuncStateToJson("SprintCD", ifnosprintcd);
		}

		ImGui::SameLine();
		HelpMarker("Removes delay in-between sprints.");
	}
}