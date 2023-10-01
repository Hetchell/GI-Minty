#include "godmode.h"

namespace cheat {
	void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime);
	bool Miscs_CheckTargetAttackableH(app::BaseEntity* attacker, app::BaseEntity* target, bool idk);

	Godmode::Godmode() {
		HookManager::install(app::Miscs_CheckTargetAttackable, Miscs_CheckTargetAttackableH);
		HookManager::install(app::VCHumanoidMove_NotifyLandVelocity, VCHumanoidMove_NotifyLandVelocity_Hook);
	}

	void Godmode::GUI() {
		ImGui::Checkbox("Godmode", &ifGodmode);
		if (ifGodmode) {
			ImGui::Indent();
			godModeHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void Godmode::Outer() {
		if (godModeHotkey.IsPressed()) {
			ifGodmode = !ifGodmode;
		}
	}

	void Godmode::Status() {
		if (ifGodmode) {
			ImGui::Text("Godmode");
		}
	}

	void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime)
	{
		if (Godmode::ifGodmode && -velocity.y > 13)
		{
			float randAdd = (float)(std::rand() % 1000) / 1000;
			velocity.y = -8 - randAdd;
			reachMaxDownVelocityTime = 0;
		}
		CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_Hook, __this, velocity, reachMaxDownVelocityTime);
	}

	bool Miscs_CheckTargetAttackableH(app::BaseEntity* attacker, app::BaseEntity* target, bool idk)
	{
		if (Godmode::ifGodmode && app::get_entityType(target) == app::EntityType__Enum_1::Avatar) {
			return false;
		}
		return CALL_ORIGIN(Miscs_CheckTargetAttackableH, attacker, target, idk);
	}
}