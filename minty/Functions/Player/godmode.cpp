#include "GodMode.h"

namespace cheat {
	static void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime);
	static bool Miscs_CheckTargetAttackableH(app::BaseEntity* attacker, app::BaseEntity* target, bool idk);

	GodMode::GodMode() {
		f_Enabled = config::getValue("functions:GodMode", "enabled", false);

		HookManager::install(app::Miscs_CheckTargetAttackable, Miscs_CheckTargetAttackableH);
		HookManager::install(app::VCHumanoidMove_NotifyLandVelocity, VCHumanoidMove_NotifyLandVelocity_Hook);
	}

	GodMode& GodMode::getInstance() {
		static GodMode instance;
		return instance;
	}

	void GodMode::GUI() {
		ConfigCheckbox("God Mode", f_Enabled);

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			godModeHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void GodMode::Outer() {
		if (godModeHotkey.IsPressed())
			f_Enabled.setValue(f_Enabled.getValue());
	}

	void GodMode::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("GodMode");
	}

	std::string GodMode::getModule() {
		return _("Player");
	}

	void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime) {
		auto& GodMode = GodMode::getInstance();

		if (GodMode.f_Enabled.getValue() && -velocity.y > 13) {
			float randAdd = (float)(std::rand() % 1000) / 1000;
			velocity.y = -8 - randAdd;
			reachMaxDownVelocityTime = 0;
		}
		CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_Hook, __this, velocity, reachMaxDownVelocityTime);
	}

	bool Miscs_CheckTargetAttackableH(app::BaseEntity* attacker, app::BaseEntity* target, bool idk) {
		auto& GodMode = GodMode::getInstance();

		if (GodMode.f_Enabled.getValue() && app::get_entityType(target) == app::EntityType__Enum_1::Avatar)
			return false;
		return CALL_ORIGIN(Miscs_CheckTargetAttackableH, attacker, target, idk);
	}
}
