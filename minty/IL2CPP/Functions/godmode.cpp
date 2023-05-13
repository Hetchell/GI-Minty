#include "godmode.h"

void VCHumanoidMove_NotifyLandVelocity_HookOn(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime)
{
	if (true && -velocity.y > 13)
	{
		float randAdd = (float)(std::rand() % 1000) / 1000;
		velocity.y = -8 - randAdd;
		reachMaxDownVelocityTime = 0;
	}
	CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_HookOn, __this, velocity, reachMaxDownVelocityTime);
}

void VCHumanoidMove_NotifyLandVelocity_HookOff(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime)
{
	CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_HookOff, __this, velocity, reachMaxDownVelocityTime);
}

bool MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUpOn(app::ActorAbilityPlugin* __this, float delay, app::Object* arg)
{
	return false;
}

bool MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUpOff(app::ActorAbilityPlugin* __this, float delay, app::Object* arg)
{
	return CALL_ORIGIN(MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUpOff, __this, delay, arg);
}

bool Miscs_CheckTargetAttackableOn(app::BaseEntity* attacker, app::BaseEntity* target)
{
	return false;
}

bool Miscs_CheckTargetAttackableOff(app::BaseEntity* attacker, app::BaseEntity* target)
{
	return CALL_ORIGIN(Miscs_CheckTargetAttackableOff, attacker, target);
}


namespace il2fns {
	void GodMode(bool value) {
		if (value) {
			HookManager::install(app::VCHumanoidMove_NotifyLandVelocity, VCHumanoidMove_NotifyLandVelocity_HookOn);
			HookManager::install(app::MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUpOn);
		}
		else {
			HookManager::detach(VCHumanoidMove_NotifyLandVelocity_HookOn);
			HookManager::install(app::VCHumanoidMove_NotifyLandVelocity, VCHumanoidMove_NotifyLandVelocity_HookOff);
			HookManager::detach(MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUpOn);
			HookManager::install(app::MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUpOff);
		}
	}
}