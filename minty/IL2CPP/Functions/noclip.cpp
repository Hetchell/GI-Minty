#include "noclip.h"
namespace il2fns {
	void OnNoclip(bool ifnoclip) {
		app::Vector3 zero;
		static bool isApplied = false;
		static std::string ActiveHero;
		app::Rigidbody* rigidbody = nullptr;
		app::GameObject* nameAvatar = nullptr;
		app::Transform* avatarTransform = nullptr;

		app::GameObject* camObj;
		app::Camera* camCam;
		app::CameraEntity* camCamEnt;

		if (!ifnoclip && isApplied)
		{
			auto AvatarRoot = app::UnityEngine__GameObject__Find(il2cpp_string_new("/EntityRoot/AvatarRoot"));

			if (AvatarRoot != nullptr) {
				auto Transform = app::UnityEngine_GameObject_GetComponent(AvatarRoot, il2cpp_string_new("Transform"));
				auto HeroCount = app::UnityEngine_Transform_GetChildCount(reinterpret_cast<app::Transform*>(Transform));

				for (int i = 0; i <= HeroCount - 1; i++)
				{
					auto HeroComponent = app::Transform_GetChild(reinterpret_cast<app::Transform*>(Transform), i);
					auto HeroGameObject = app::Component_1_get_gameObject(reinterpret_cast<app::Component_1*>(HeroComponent));
					auto isActiveHero = app::GameObject_get_active(HeroGameObject);

					if (isActiveHero)
					{
						auto GameObjectName = app::Object_1_get_name(reinterpret_cast<app::Object_1*>(HeroGameObject));
						ActiveHero = il2cppi_to_string3(GameObjectName);
						std::string Hero = ActiveHero.erase(ActiveHero.find("(Clone)"));
						util::log(2, "active hero is %s", ActiveHero);

						std::string avatarNamestring = "/EntityRoot/AvatarRoot/" + il2cppi_to_string3(GameObjectName) + "/OffsetDummy/" + Hero.c_str();

						nameAvatar = app::UnityEngine__GameObject__Find(il2cpp_string_new(avatarNamestring.c_str()));
						avatarTransform = app::UnityEngine__Component__get__Transform(nameAvatar);

						rigidbody = reinterpret_cast<app::Rigidbody*>(app::UnityEngine_GameObject_GetComponent(nameAvatar, il2cpp_string_new("Rigidbody")));
						if (rigidbody == nullptr)
							util::log(2, "no rigidbody");
					}
				}
			}

			//auto rigidBody = avatarEntity->rigidbody();
			if (rigidbody == nullptr)
				return;

			app::Rigidbody_set_detectCollisions(rigidbody, true);

			isApplied = false;
		}

		if (!ifnoclip)
			return;

		isApplied = true;

		//auto avatarEntity = manager.avatar();
		//auto baseMove = avatarEntity->moveComponent();
		//if (baseMove == nullptr)
		//	return;

		//auto rigidBody = avatarEntity->rigidbody();
		//if (rigidBody == nullptr)
		//	return;

		app::Rigidbody_set_collisionDetectionMode(rigidbody, app::CollisionDetectionMode__Enum::Continuous);
		app::Rigidbody_set_detectCollisions(rigidbody, false);

		//app::Rigidbody_set_velocity(rigidBody, zero);

		auto cameraEntity = reinterpret_cast<app::BaseEntity*>(app::UnityEngine__GameObject__Find(il2cpp_string_new("/EntityRoot/MainCamera(clone)")));
		auto avatarEntity = reinterpret_cast<app::BaseEntity*>(nameAvatar);
		//auto relativeEntity = &cameraEntity;

		float speed = 20;
		//if (f_AltSpeedEnabled ? f_UseCustomKeys ? f_AltSpeedKey.value().IsPressed() : Hotkey(ImGuiKey_ModCtrl).IsPressed() : NULL)
		//	speed = f_AltSpeed.value();

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

		app::Vector3 prevPos = app::MoleMole_BaseEntity_GetRelativePosition(avatarEntity);
		if (prevPos.x == 0 && prevPos.y == 0 && prevPos.z == 0)
			return;

		float deltaTime = app::Time_get_deltaTime();

		app::Vector3 newPos = prevPos + dir * speed * deltaTime;
		app::Transform_Translate(avatarTransform, newPos);
	}
}