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

static std::string ActiveHero;
bool ifAvatarOD(app::BaseEntity* target) {
	auto AvatarRoot = app::UnityEngine__GameObject__Find(string_to_il2cppii("/EntityRoot/AvatarRoot"));

	if (AvatarRoot != nullptr) {
		auto Transform = app::UnityEngine_GameObject_GetComponent(AvatarRoot, string_to_il2cppii("Transform"));
		auto HeroCount = app::UnityEngine_Transform_GetChildCount(reinterpret_cast<app::Transform*>(Transform));

		for (int i = 0; i <= HeroCount - 1; i++)
		{
			auto HeroComponent = app::Transform_GetChild(reinterpret_cast<app::Transform*>(Transform), i);
			auto HeroGameObject = app::Component_1_get_gameObject(reinterpret_cast<app::Component_1*>(HeroComponent));
			auto isActiveHero = app::GameObject_get_active(HeroGameObject);

			if (isActiveHero)
			{
				auto GameObjectName = app::Object_1_get_name(reinterpret_cast<app::Object_1*>(HeroGameObject));
				ActiveHero = il2cppi_to_stringgm(GameObjectName);
				std::string Hero = ActiveHero.erase(ActiveHero.find("(Clone)"));
				util::log(M_Info, "active hero is %s", ActiveHero);

				std::string nameL = "/EntityRoot/AvatarRoot/" + il2cppi_to_stringgm(GameObjectName) + "/OffsetDummy/";
				auto AvatarObj = app::UnityEngine__GameObject__Find(string_to_il2cppii(nameL));

				if (AvatarObj == target->fields._offsetDummyObject) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
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