#include "godmode.h"

static bool ifgod;
static bool ifinit;

void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime)
{
	if (ifgod && -velocity.y > 13)
	{
		float randAdd = (float)(std::rand() % 1000) / 1000;
		velocity.y = -8 - randAdd;
		reachMaxDownVelocityTime = 0;
	}
	CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_Hook, __this, velocity, reachMaxDownVelocityTime);
}

bool Miscs_CheckTargetAttackableH(app::BaseEntity* attacker, app::BaseEntity* target, bool idk)
{
	if (ifgod && app::get_entityType(target) == app::EntityType__Enum_1::Avatar) {
		return false;
	}
	return CALL_ORIGIN(Miscs_CheckTargetAttackableH, attacker, target, idk);
}

namespace il2fns {
	void GodMode(bool value) {
		if (!ifinit) {
			HookManager::install(app::Miscs_CheckTargetAttackable, Miscs_CheckTargetAttackableH);
			HookManager::install(app::VCHumanoidMove_NotifyLandVelocity, VCHumanoidMove_NotifyLandVelocity_Hook); ifinit = true;
		}
		ifgod = value;
	}
}