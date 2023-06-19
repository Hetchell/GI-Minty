#include "noclip.h"

namespace il2fns {
	static bool ifnoclip, bInitNoClip, isApplied;
	static int iNoClipMode;
	int iColMode;
	static float speed = 10;
	app::Vector3 prevPos, newPos;
	app::Vector3 posCheck;

	void noclipmod(int i) {
		iNoClipMode = i;
	}
	
	void colmod(int i) {
		iColMode = i;
	}

	void OnNoclip() {
		static std::string ActiveHero;

		app::Rigidbody* rigidbody = nullptr;
		app::GameObject* AvatarRoot = nullptr;
		app::GameObject* nameAvatar = nullptr;
		app::Transform* avatarTransform = nullptr;
		app::GameObject* HeroGameObject = nullptr;

		AvatarRoot = app::UnityEngine__GameObject__Find(string_to_il2cppi("/EntityRoot/AvatarRoot"));
		if (!AvatarRoot) return;
		auto Transform = app::UnityEngine_GameObject_GetComponent(AvatarRoot, string_to_il2cppi("Transform"));
		auto HeroCount = app::UnityEngine_Transform_GetChildCount(reinterpret_cast<app::Transform*>(Transform));
		for (int i = 0; i <= HeroCount - 1; i++)
		{
			auto HeroComponent = app::Transform_GetChild(reinterpret_cast<app::Transform*>(Transform), i);
			HeroGameObject = app::Component_1_get_gameObject(reinterpret_cast<app::Component_1*>(HeroComponent));
			auto isActiveHero = app::GameObject_get_active(HeroGameObject);
			if (isActiveHero)
			{
				auto GameObjectName = app::Object_1_get_name(reinterpret_cast<app::Object_1*>(HeroGameObject));
				ActiveHero = il2cppi_to_string(GameObjectName);
				std::string Hero = ActiveHero.erase(ActiveHero.find("(Clone)"));
				std::string avatarNamestring = "/EntityRoot/AvatarRoot/" + il2cppi_to_string(GameObjectName) + "/OffsetDummy/" + Hero.c_str();
				nameAvatar = app::UnityEngine__GameObject__Find(string_to_il2cppi(avatarNamestring.c_str()));
				avatarTransform = app::UnityEngine__Component__get__Transform(nameAvatar);
				rigidbody = reinterpret_cast<app::Rigidbody*>(app::UnityEngine_GameObject_GetComponent(HeroGameObject, string_to_il2cppi("Rigidbody")));
				if (rigidbody != 0) break;
			}
		}

		if (!ifnoclip && isApplied)
		{
			if (rigidbody == nullptr)
				return;
			prevPos = { 0, 0, 0 };
			app::Rigidbody_set_detectCollisions(rigidbody, true);
			isApplied = false;
		}

		isApplied = true;

		app::Rigidbody_set_collisionDetectionMode(rigidbody, app::CollisionDetectionMode__Enum::Continuous);
		if (iColMode == 1) {
			app::Rigidbody_set_detectCollisions(rigidbody, true);
		}
		else if (iColMode == 0) {
			app::Rigidbody_set_detectCollisions(rigidbody, false);
		}

		auto cameraEntity = reinterpret_cast<app::BaseEntity*>(app::UnityEngine__Component__get__Transform(app::UnityEngine__GameObject__Find(string_to_il2cppi("/EntityRoot/MainCamera(Clone)(Clone)"))));
		auto avatarEntity = reinterpret_cast<app::BaseEntity*>(avatarTransform);

		app::Vector3 dir = {};

		if (ImGui::IsKeyDown(ImGuiKey_W))
			dir = dir + app::MoleMole_BaseEntity_GetForward(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_S))
			dir = dir - app::MoleMole_BaseEntity_GetForward(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_D))
			dir = dir + app::MoleMole_BaseEntity_GetRight(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_A))
			dir = dir - app::MoleMole_BaseEntity_GetRight(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_Space))
			dir = dir + app::MoleMole_BaseEntity_GetUp(avatarEntity);

		if (ImGui::IsKeyDown(ImGuiKey_ModShift))
			dir = dir - app::MoleMole_BaseEntity_GetUp(avatarEntity);

		prevPos = app::Rigidbody_get_position(rigidbody);
		if (prevPos.x == 0 && prevPos.y == 0 && prevPos.z == 0)
			return;

		float deltaTime = app::Time_get_deltaTime() * 1.5;
		newPos = prevPos + dir * speed * deltaTime;
		// if (iNoClipMode == 0) 
		app::Rigidbody_set_velocity(rigidbody, { 0,0,0 });
		app::Rigidbody_MovePosition(rigidbody, newPos);
		//app::Rigidbody_set_position(rigidbody, newPos);
	}

	void GameManager_Update_Hook(app::GameManager* __this, app::MethodInfo* method)
	{
		__try {
			//if (ifnoclip) OnNoclip();
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			util::log(M_Error, "Exception 0x%08x.", _exception_code());
		}

		CALL_ORIGIN(GameManager_Update_Hook, __this, method);
	}

	void HumanoidMoveFSM_LateTick_Hook(app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method)
	{
		if (ifnoclip && iNoClipMode == 0) {
			if (app::Vector3_Distance(posCheck, newPos) > 3.f) {
				posCheck = newPos;
			}
			else {
				return;
			}
		}

		CALL_ORIGIN(HumanoidMoveFSM_LateTick_Hook, __this, deltaTime, method);
	}

	void NoClipInit(bool b) {
		ifnoclip = b;
		if (!bInitNoClip) {
			HookManager::install(app::GameManager_Update, GameManager_Update_Hook);
			HookManager::install(app::MoleMole_HumanoidMoveFSM_LateTick, HumanoidMoveFSM_LateTick_Hook);
			bInitNoClip = true;
		}
	}

	void NoClipSpeed(float f) {
		speed = f;
	}
}