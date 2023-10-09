#include "nocd.h"

namespace cheat {
	static bool LCAvatarCombat_OnSkillStart(app::LCAvatarCombat* __this, uint32_t skillID, float cdMultipler);
	static void ActorAbilityPlugin_AddDynamicFloatWithRange_Hook(app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minValue, float maxValue, bool forceDoAtRemote);
	static bool HumanoidMoveFSM_CheckSprintCooldown_Hook(void* __this);

	NoCD::NoCD() {
		HookManager::install(app::LCAvatarCombat_OnSkillStart, LCAvatarCombat_OnSkillStart);
		HookManager::install(app::MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, ActorAbilityPlugin_AddDynamicFloatWithRange_Hook);
		HookManager::install(app::MoleMole_HumanoidMoveFSM_CheckSprintCooldown, HumanoidMoveFSM_CheckSprintCooldown_Hook);
	}

	void NoCD::GUI() {
		ImGui::Checkbox(_("No skill CD"), &ifNoSkillCD);
		if (ifNoSkillCD) {
			ImGui::Indent();
			noSkillCDHotkey.Draw();
			ImGui::Unindent();
		}
		ImGui::Checkbox(_("Instant bow charge"), &ifNoBowCD);
		if (ifNoBowCD) {
			ImGui::Indent();
			noBowCDHotkey.Draw();
			ImGui::Unindent();
		}
		ImGui::Checkbox(_("No sprint CD"), &ifNoSprintCD);
		if (ifNoSprintCD) {
			ImGui::Indent();
			noSprintCDHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void NoCD::Outer() {
		if (noSkillCDHotkey.IsPressed()) {
			ifNoSkillCD = !ifNoSkillCD;
		}
		if (noBowCDHotkey.IsPressed()) {
			ifNoBowCD = !ifNoBowCD;
		}
		if (noSprintCDHotkey.IsPressed()) {
			ifNoSprintCD = !ifNoSprintCD;
		}
	}

	void NoCD::Status() {
		if (ifNoSkillCD) {
			ImGui::Text("NoSkillCD");
		}
		if (ifNoSkillCD) {
			ImGui::Text("InstantBow");
		}
		if (ifNoSprintCD) {
			ImGui::Text("NoSprintCD");
		}
	}

	static bool LCAvatarCombat_OnSkillStart(app::LCAvatarCombat* __this, uint32_t skillID, float cdMultipler) {
		if (NoCD::ifNoSkillCD)
		{
			cdMultipler = 0;
		}
		return CALL_ORIGIN(LCAvatarCombat_OnSkillStart, __this, skillID, cdMultipler);
	}

	static void ActorAbilityPlugin_AddDynamicFloatWithRange_Hook(app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minValue, float maxValue, bool forceDoAtRemote) {
		if (NoCD::ifNoBowCD && il2cppi_to_string(key) == "_Enchanted_Time")
		{
			value = maxValue;
			//util::log(M_Info, "value: %d, minValue: %d, maxValue: %d, nextValidAbilityID: %d", value, minValue, maxValue, __this->fields.nextValidAbilityID);
			//__this->fields.nextValidAbilityID = 36; --- FIELDS!!!!!!
		}
		CALL_ORIGIN(ActorAbilityPlugin_AddDynamicFloatWithRange_Hook, __this, key, value, minValue, maxValue, forceDoAtRemote);
	}

	static bool HumanoidMoveFSM_CheckSprintCooldown_Hook(void* __this)
	{
		if (NoCD::ifNoSprintCD)
			return true;
		return CALL_ORIGIN(HumanoidMoveFSM_CheckSprintCooldown_Hook, __this);
	}
}
