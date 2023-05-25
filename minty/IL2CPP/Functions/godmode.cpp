#include "godmode.h"

static bool ifgod;
static bool ifinit;
void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime)
{
	if (ifgod && -velocity.y > 13)
	{
		try {
			float randAdd = (float)(std::rand() % 1000) / 1000;
			velocity.y = -8 - randAdd;
			reachMaxDownVelocityTime = 0;
		}
		catch (...) {}
	}
	CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_Hook, __this, velocity, reachMaxDownVelocityTime);
}

namespace il2fns {
	void GodMode(bool value) {
		if (!ifinit)
			HookManager::install(app::VCHumanoidMove_NotifyLandVelocity, VCHumanoidMove_NotifyLandVelocity_Hook); ifinit = true;
		ifgod = value;
	}
}