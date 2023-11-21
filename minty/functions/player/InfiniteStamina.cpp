#include "InfiniteStamina.h"

namespace cheat {
	static void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state);
	static void VCHumanoidMove_Scara_Hook(app::VCHumanoidMove* __this, float value);
	static void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq);

	InfiniteStamina::InfiniteStamina() {
		f_Enabled = config::getValue("functions:InfiniteStamina", "enabled", false);
		f_EnabledPacket = config::getValue("functions:InfiniteStamina", "packetReplacement", false);

		f_Hotkey = Hotkey("functions:InfiniteStamina");

		HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_Hook);
		HookManager::install(app::VCHumanoidMove_Scara, VCHumanoidMove_Scara_Hook);
		HookManager::install(app::MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook);
	}

	InfiniteStamina& InfiniteStamina::getInstance() {
		static InfiniteStamina instance;
		return instance;
	}

	void InfiniteStamina::GUI() {
		ConfigCheckbox("Infinite Stamina", f_Enabled, "Enables infinite stamina option.");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigCheckbox("Move Sync Packet Replacement", f_EnabledPacket, "This mode prevents sending server packets with stamina cost actions,\n"
				"e.g. swim, climb, sprint, etc.");
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void InfiniteStamina::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void InfiniteStamina::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("Infinite Stamina");
	}

	std::string InfiniteStamina::getModule() {
		return _("Player");
	}

	bool InfiniteStamina::OnPropertySet(app::PropType__Enum propType) {
		using PT = app::PropType__Enum;
		static bool override_cheat = true;

		if (propType == PT::PROP_CUR_TEMPORARY_STAMINA)
			override_cheat = true;

		const bool result = !f_Enabled.getValue() || f_EnabledPacket.getValue() || //override_cheat ||
			(propType != PT::PROP_MAX_STAMINA &&
				propType != PT::PROP_CUR_PERSIST_STAMINA &&
				propType != PT::PROP_CUR_TEMPORARY_STAMINA &&
				propType != PT::PROP_MAX_DIVE_STAMINA &&
				propType != PT::PROP_CUR_PERSIST_DIVE_STAMINA);

		if (propType == PT::PROP_MAX_STAMINA)
			override_cheat = false;
		return result;
	}

	void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo,
		bool isReliable, uint32_t reliableSeq) {
		static bool afterDash = false;

		auto& infiniteStamina = InfiniteStamina::getInstance();
		auto& manager = game::EntityManager::getInstance();
		auto entity = manager.entity(entityId);

		if (entity->type() == app::EntityType__Enum_1::Vehicle || entity->isAvatar()) {
			// LOG_DEBUG("Movement packet: %s", magic_enum::enum_name(app::MotionInfo_get_State(syncInfo)).data());
			if (infiniteStamina.f_Enabled.getValue() && infiniteStamina.f_EnabledPacket.getValue()) {
				auto state = app::MotionInfo_get_State(syncInfo);
				switch (state) {
				case app::MotionState__Enum::MotionDash:
				case app::MotionState__Enum::MotionClimb:
				case app::MotionState__Enum::MotionClimbJump:
				case app::MotionState__Enum::MotionStandbyToClimb:
				case app::MotionState__Enum::MotionSwimDash:
				case app::MotionState__Enum::MotionSwimIdle:
				case app::MotionState__Enum::MotionSwimMove:
				case app::MotionState__Enum::MotionSwimJump:
				case app::MotionState__Enum::MotionDiveDash:
				case app::MotionState__Enum::MotionDiveIdle:
				case app::MotionState__Enum::MotionDiveSwimDash:
				case app::MotionState__Enum::MotionDiveSwimIdle:
				case app::MotionState__Enum::MotionFly:
				case app::MotionState__Enum::MotionFight:
				case app::MotionState__Enum::MotionDashBeforeShake:
				case app::MotionState__Enum::MotionDangerDash:
					app::MotionInfo_set_State(syncInfo, app::MotionState__Enum::MotionRun);
					break;
				case app::MotionState__Enum::MotionJump:
					if (afterDash)
						app::MotionInfo_set_State(syncInfo, app::MotionState__Enum::MotionRun);
					break;
				case app::MotionState__Enum::MotionSkiffDash:
				case app::MotionState__Enum::MotionSkiffPoweredDash:
					app::MotionInfo_set_State(syncInfo, app::MotionState__Enum::MotionSkiffNormal);
					break;
				}

				if (state != app::MotionState__Enum::MotionJump && state != app::MotionState__Enum::MotionFallOnGround)
					afterDash = state == app::MotionState__Enum::MotionDash;
			}
		}

		CALL_ORIGIN(LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook, __this, entityId, syncInfo, isReliable, reliableSeq);
	}

	void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state) {
		auto& infiniteStamina = InfiniteStamina::getInstance();
		auto propType = static_cast<app::PropType__Enum>(type);
		bool isValid = infiniteStamina.OnPropertySet(propType);

		if (isValid)
			CALL_ORIGIN(DataItem_HandleNormalProp_Hook, __this, type, value, state);
	}

	void VCHumanoidMove_Scara_Hook(app::VCHumanoidMove* __this, float value) {
		auto& infiniteStamina = InfiniteStamina::getInstance();

		if (infiniteStamina.f_Enabled.getValue())
			value = 34028234663852885981170418348451692544.f;
		CALL_ORIGIN(VCHumanoidMove_Scara_Hook, __this, value);
	}
}
