#include "NoCooldown.h"

namespace cheat {
	static bool LCAvatarCombat_OnSkillStart(app::LCAvatarCombat* __this, uint32_t skillID, float multipler);
	static void ActorAbilityPlugin_AddDynamicFloatWithRange_Hook(app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minValue, float maxValue, bool forceDoAtRemote);
	static bool HumanoidMoveFSM_CheckSprintCooldown_Hook(void* __this);

	NoCooldown::NoCooldown() {
		f_EnabledSkill = config::getValue("functions:NoCooldown:Skill", "enabled", false);
		f_EnabledBow = config::getValue("functions:NoCooldown:Bow", "enabled", false);
		f_EnabledSprint = config::getValue("functions:NoCooldown:Sprint", "enabled", false);
		f_HotkeySkill = Hotkey("functions:NoCooldown:Skill");
		f_HotkeyBow = Hotkey("functions:NoCooldown:Bow");
		f_HotkeySprint = Hotkey("functions:NoCooldown:Sprint");

		HookManager::install(app::LCAvatarCombat_OnSkillStart, LCAvatarCombat_OnSkillStart);
		HookManager::install(app::MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, ActorAbilityPlugin_AddDynamicFloatWithRange_Hook);
		HookManager::install(app::MoleMole_HumanoidMoveFSM_CheckSprintCooldown, HumanoidMoveFSM_CheckSprintCooldown_Hook);
	}

	NoCooldown& NoCooldown::getInstance() {
		static NoCooldown instance;
		return instance;
	}

	void NoCooldown::GUI() {
		ConfigCheckbox(_("No Skill Cooldown"), f_EnabledSkill, "Remove cooldowns of elemental skills and bursts.");

		if (f_EnabledSkill.getValue()) {
			ImGui::Indent();
			f_HotkeySkill.Draw();
			ImGui::Unindent();
		}

		ConfigCheckbox(_("Instant Bow Charge"), f_EnabledBow, "Disable cooldown of bow charge.\n"
			"Known issues with Fischl.");

		if (f_EnabledBow.getValue()) {
			ImGui::Indent();
			f_HotkeyBow.Draw();
			ImGui::Unindent();
		}

		ConfigCheckbox(_("No Sprint Cooldown"), f_EnabledSprint, "Removes delay in-between sprints.");

		if (f_EnabledSprint.getValue()) {
			ImGui::Indent();
			f_HotkeySprint.Draw();
			ImGui::Unindent();
		}
	}

	void NoCooldown::Outer() {
		if (f_HotkeySkill.IsPressed())
			f_EnabledSkill.setValue(!f_EnabledSkill.getValue());

		if (f_HotkeyBow.IsPressed())
			f_EnabledBow.setValue(!f_EnabledBow.getValue());

		if (f_HotkeySprint.IsPressed())
			f_EnabledSprint.setValue(!f_EnabledSprint.getValue());
	}

	void NoCooldown::Status() {
		if (f_EnabledSkill.getValue())
			ImGui::Text("NoSkillCD");

		if (f_EnabledBow.getValue())
			ImGui::Text("InstantBow");

		if (f_EnabledSprint.getValue())
			ImGui::Text("NoSprintCD");
	}

	std::string NoCooldown::getModule() {
		return _("Player");
	}

	bool LCAvatarCombat_OnSkillStart(app::LCAvatarCombat* __this, uint32_t skillID, float multipler) {
		auto& NoCooldown = NoCooldown::getInstance();

		if (NoCooldown.f_EnabledSkill.getValue())
			multipler = 0;
		return CALL_ORIGIN(LCAvatarCombat_OnSkillStart, __this, skillID, multipler);
	}

	void ActorAbilityPlugin_AddDynamicFloatWithRange_Hook(app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minValue, float maxValue, bool forceDoAtRemote) {
		auto& NoCooldown = NoCooldown::getInstance();
		
		if (NoCooldown.f_EnabledBow.getValue() && il2cppi_to_string(key) == "_Enchanted_Time") {
			value = maxValue;
			//LOG_INFO("value: %d, minValue: %d, maxValue: %d, nextValidAbilityID: %d", value, minValue, maxValue, __this->fields.nextValidAbilityID);
			//__this->fields.nextValidAbilityID = 36;
		}
		CALL_ORIGIN(ActorAbilityPlugin_AddDynamicFloatWithRange_Hook, __this, key, value, minValue, maxValue, forceDoAtRemote);
	}

	bool HumanoidMoveFSM_CheckSprintCooldown_Hook(void* __this) {
		auto& NoCooldown = NoCooldown::getInstance();

		if (NoCooldown.f_EnabledSprint.getValue())
			return true;
		return CALL_ORIGIN(HumanoidMoveFSM_CheckSprintCooldown_Hook, __this);
	}
}
