#include "noclip.h"

void OnNoclip() {
	app::Vector3 zero;
	static bool isApplied = false;

	if (isApplied)
	{
		auto avatarEntity = manager.avatar();
		auto rigidBody = avatarEntity->rigidbody();
		if (rigidBody == nullptr)
			return;

		app::Rigidbody_set_detectCollisions(rigidBody, true, nullptr);

		isApplied = false;
	}

	if (!f_Enabled)
		return;

	isApplied = true;

	auto avatarEntity = manager.avatar();
	auto baseMove = avatarEntity->moveComponent();
	if (baseMove == nullptr)
		return;

	if (renderer::IsInputLocked())
		return;

	auto rigidBody = avatarEntity->rigidbody();
	if (rigidBody == nullptr)
		return;

	if (!f_FreeflightMode)
	{
		app::Rigidbody_set_collisionDetectionMode(rigidBody, app::CollisionDetectionMode__Enum::Continuous, nullptr);
		app::Rigidbody_set_detectCollisions(rigidBody, false, nullptr);
	}

	if (!f_VelocityMode)
		app::Rigidbody_set_velocity(rigidBody, zero, nullptr);

	auto cameraEntity = game::Entity(reinterpret_cast<app::BaseEntity*>(manager.mainCamera()));
	auto relativeEntity = f_CameraRelative ? &cameraEntity : avatarEntity;

	float speed = f_Speed.value();
	if (f_AltSpeedEnabled ? f_UseCustomKeys ? f_AltSpeedKey.value().IsPressed() : Hotkey(ImGuiKey_ModCtrl).IsPressed() : NULL)
		speed = f_AltSpeed.value();

	app::Vector3 dir = {};

	if (f_UseCustomKeys ? f_ForwardKey.value().IsPressed() : Hotkey(ImGuiKey_W).IsPressed())
		dir = dir + relativeEntity->forward();

	if (f_UseCustomKeys ? f_BackKey.value().IsPressed() : Hotkey(ImGuiKey_S).IsPressed())
		dir = dir + relativeEntity->back();

	if (f_UseCustomKeys ? f_RightKey.value().IsPressed() : Hotkey(ImGuiKey_D).IsPressed())
		dir = dir + relativeEntity->right();

	if (f_UseCustomKeys ? f_LeftKey.value().IsPressed() : Hotkey(ImGuiKey_A).IsPressed())
		dir = dir + relativeEntity->left();

	if (f_UseCustomKeys ? f_AscendKey.value().IsPressed() : Hotkey(ImGuiKey_Space).IsPressed())
		dir = dir + avatarEntity->up();

	if (f_UseCustomKeys ? f_DescendKey.value().IsPressed() : Hotkey(ImGuiKey_ModShift).IsPressed())
		dir = dir + avatarEntity->down();

	app::Vector3 prevPos = avatarEntity->relativePosition();
	if (IsVectorZero(prevPos))
		return;

	float deltaTime = app::Time_get_deltaTime(nullptr);

	app::Vector3 newPos = prevPos + dir * speed * deltaTime;
	if (!f_VelocityMode)
		avatarEntity->setRelativePosition(newPos);
	else
		app::Rigidbody_set_velocity(rigidBody, dir * speed);
}