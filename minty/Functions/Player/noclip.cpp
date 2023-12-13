#include "NoClip.h"

namespace cheat {
	void GameManager_Update_Hook(app::GameManager* __this, app::MethodInfo* method);
	void HumanoidMoveFSM_LateTick_Hook(app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method);
	void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq);

	app::Vector3 dir;

	NoClip::NoClip() {
		f_Enabled = config::getValue("functions:NoClip", "enabled", false);
		f_EnabledAltSpeed = config::getValue("functions:NoClip:Alt", "enabled", false);
		f_NoAnimation = config::getValue("functions:NoClip", "noAnimation", false);
		f_DetectCollisions = config::getValue("functions:NoClip", "detectCollisions", true);
		f_Speed = config::getValue("functions:NoClip", "speed", 5.0f);
		f_AltSpeed = config::getValue("functions:NoClip:Alt", "speed", 10.0f);
		f_Hotkey = Hotkey("functions:NoClip");
		f_HotkeyAlt = Hotkey("functions:NoClip:Alt", VK_LCONTROL);

		HookManager::install(app::GameManager_Update, GameManager_Update_Hook);
		HookManager::install(app::MoleMole_HumanoidMoveFSM_LateTick, HumanoidMoveFSM_LateTick_Hook);
		HookManager::install(app::MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook);
	}

	NoClip& NoClip::getInstance() {
		static NoClip instance;
		return instance;
	}

	void NoClip::GUI() {
		ConfigCheckbox("No Clip", f_Enabled, "Enables No Clip (fast speed + no collision).\n"
			"To move, use WASD, Space (go up), and Shift (go down).");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat("Speed", f_Speed, 0.1f, 100.0f, "No Clip move speed.\n"
				"Not recommended setting above 5.0.");
			ConfigCheckbox("No Animation", f_NoAnimation, "Disables player animations.");
			ConfigCheckbox("Detect collisions", f_DetectCollisions, "Allows the player to go thrught textures(it breaks some of the game mechanics).");
			ConfigCheckbox("Alternate No Clip", f_EnabledAltSpeed, "Allows usage of alternate speed when holding down LeftCtrl key.\n"
				"Useful if you want to temporarily go faster/slower than the No Clip speed setting.");
			if (f_EnabledAltSpeed.getValue()) {
				ImGui::Indent();
				ConfigSliderFloat("Alternate Speed", f_AltSpeed, 0.1f, 100.0f, "Alternate No Clip move speed.\n"
					"Not recommended setting above 5.0.");
				f_HotkeyAlt.Draw();
				ImGui::Unindent();
			}
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void NoClip::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());

		if (f_EnabledAltSpeed.getValue() && f_HotkeyAlt.IsDown())
			f_finalSpeed = f_AltSpeed.getValue();
		else
			f_finalSpeed = f_Speed.getValue();
	}

	void NoClip::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("Noclip (%.1f U/s | %.1f U/s ", f_Speed.getValue(), f_AltSpeed.getValue());
	}

	std::string NoClip::getModule() {
		return _("Player");
	}

	void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq) {
		auto& noClip = NoClip::getInstance();
		
		static app::Vector3 prevPosition = {};
		static int64_t prevSyncTime = 0;

		if (!noClip.f_Enabled.getValue())
		{
			prevSyncTime = 0;
			return;
		}

		auto& manager = game::EntityManager::getInstance();
		if (manager.avatar()->runtimeID() != entityId)
			return;

		auto avatarEntity = manager.avatar();
		if (avatarEntity == nullptr)
			return;

		auto avatarPosition = avatarEntity->absolutePosition();
		auto currentTime = util::GetCurrentTimeMillisec();
		if (prevSyncTime > 0)
		{
			auto posDiff = avatarPosition - prevPosition;
			auto timeDiff = ((float)(currentTime - prevSyncTime)) / 1000;
			auto velocity = posDiff / timeDiff;

			auto speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
			if (speed > 0.1)
			{
				syncInfo->fields.motionState = (speed < 2) ? app::MotionState__Enum::MotionWalk : app::MotionState__Enum::MotionRun;

				syncInfo->fields.speed_->fields.x = velocity.x;
				syncInfo->fields.speed_->fields.y = velocity.y;
				syncInfo->fields.speed_->fields.z = velocity.z;
			}

			syncInfo->fields.pos_->fields.x = avatarPosition.x;
			syncInfo->fields.pos_->fields.y = avatarPosition.y;
			syncInfo->fields.pos_->fields.z = avatarPosition.z;
		}

		prevPosition = avatarPosition;
		prevSyncTime = currentTime;

	}

	void OnNoClip() {
		auto& noClip = NoClip::getInstance();
		auto& manager = game::EntityManager::getInstance();

		auto avatarEntity = manager.avatar();
		if (avatarEntity == nullptr)
			return;
		auto rigidBody = avatarEntity->rigidbody();
		if (rigidBody == nullptr)
			return;
		
		if (!noClip.f_Enabled.getValue()) {
			app::Rigidbody_set_detectCollisions(rigidBody, true);
			return;
		}
		else if (!noClip.f_DetectCollisions.getValue()) {
			app::Rigidbody_set_detectCollisions(rigidBody, false);
		}

		app::Rigidbody_set_collisionDetectionMode(rigidBody, app::CollisionDetectionMode__Enum::Continuous);
		app::Rigidbody_set_velocity(rigidBody, {0,0,0});

		auto cameraEntity = game::Entity(reinterpret_cast<app::BaseEntity*>(manager.mainCamera()));
		dir = {};

		if (ImGui::IsKeyDown(ImGuiKey_W))
			dir = dir + cameraEntity.forward();

		if (ImGui::IsKeyDown(ImGuiKey_S))
			dir = dir + cameraEntity.back();

		if (ImGui::IsKeyDown(ImGuiKey_D))
			dir = dir + cameraEntity.right();

		if (ImGui::IsKeyDown(ImGuiKey_A))
			dir = dir + cameraEntity.left();

		if (ImGui::IsKeyDown(ImGuiKey_Space))
			dir = dir + avatarEntity->up();

		if (ImGui::IsKeyDown(ImGuiKey_ModShift))
			dir = dir + avatarEntity->down();


		noClip.prevPos = app::Rigidbody_get_position(rigidBody);

		if (noClip.prevPos.x == 0 && noClip.prevPos.y == 0 && noClip.prevPos.z == 0)
			return;

		float deltaTime = app::Time_get_deltaTime() * 1.5F;
		noClip.newPos = noClip.prevPos + dir * NoClip::f_finalSpeed * deltaTime;

		app::Rigidbody_MovePosition(rigidBody, noClip.newPos);
	}


	void GameManager_Update_Hook(app::GameManager* __this, app::MethodInfo* method) {
		auto& noClip = NoClip::getInstance();

		OnNoClip();

		CALL_ORIGIN(GameManager_Update_Hook, __this, method);
	}

	void HumanoidMoveFSM_LateTick_Hook(app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method) {
		auto& noClip = NoClip::getInstance();

		if (noClip.f_Enabled.getValue()) {
			if (!noClip.f_NoAnimation.getValue()) 
				__this->fields._layerMaskScene = 2;
			else 
				return;

			if (app::Vector3_Distance(noClip.posCheck, noClip.newPos) > 3.0f)
				noClip.posCheck = noClip.newPos;
			else
				return;
		}

		CALL_ORIGIN(HumanoidMoveFSM_LateTick_Hook, __this, deltaTime, method);
	}
}
