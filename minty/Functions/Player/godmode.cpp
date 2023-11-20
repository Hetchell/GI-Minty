#include "GodMode.h"

namespace cheat {
	static void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime);
	static bool Miscs_CheckTargetAttackable_Hook(app::BaseEntity* attacker, app::BaseEntity* target, bool checkBackstage);

	GodMode::GodMode() {
		f_Enabled = config::getValue("functions:GodMode", "enabled", false);
		f_Hotkey = Hotkey("functions:GodMode");

		HookManager::install(app::Miscs_CheckTargetAttackable, Miscs_CheckTargetAttackable_Hook);
		HookManager::install(app::VCHumanoidMove_NotifyLandVelocity, VCHumanoidMove_NotifyLandVelocity_Hook);
	}

	GodMode& GodMode::getInstance() {
		static GodMode instance;
		return instance;
	}

	void GodMode::GUI() {
		ConfigCheckbox("God Mode", f_Enabled, "Enables god mode, i.e. no incoming damage including environmental damage.");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void GodMode::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void GodMode::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("GodMode");
	}

	std::string GodMode::getModule() {
		return _("Player");
	}

	void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime) {
		auto& godMode = GodMode::getInstance();

		if (godMode.f_Enabled.getValue() && -velocity.y > 13) {
			float randAdd = (float)(std::rand() % 1000) / 1000;
			velocity.y = -8 - randAdd;
			reachMaxDownVelocityTime = 0;
		}
		CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_Hook, __this, velocity, reachMaxDownVelocityTime);
	}

	bool Miscs_CheckTargetAttackable_Hook(app::BaseEntity* attacker, app::BaseEntity* target, bool checkBackstage) {
		auto& godMode = GodMode::getInstance();

		if (godMode.f_Enabled.getValue() && app::MoleMole_BaseEntity_get_entityType(target) == app::EntityType__Enum_1::Avatar)
			return false;
		return CALL_ORIGIN(Miscs_CheckTargetAttackable_Hook, attacker, target, checkBackstage);
	}
}
