#include "InfiniteStamina.h"

namespace cheat {
	static bool OnPropertySet(app::PropType__Enum propType);
	static void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state);
	static void VCHumanoidMove_Scara_Hook(app::VCHumanoidMove* __this, float value);
	static void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq);

	InfiniteStamina::InfiniteStamina() {
		f_Enabled = config::getValue("functions:InfiniteStamina", "enabled", false);
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

	bool OnPropertySet(app::PropType__Enum propType) {
		auto& infiniteStamina = InfiniteStamina::getInstance();
		using PT = app::PropType__Enum;
		static bool override_cheat = true;

		if (propType == PT::PROP_CUR_TEMPORARY_STAMINA)
			override_cheat = true;

		const bool result = !infiniteStamina.f_Enabled.getValue() ||
			(propType != PT::PROP_MAX_STAMINA &&
				propType != PT::PROP_CUR_PERSIST_STAMINA &&
				propType != PT::PROP_CUR_TEMPORARY_STAMINA &&
				propType != PT::PROP_CUR_PERSIST_DIVE_STAMINA);

		if (propType == PT::PROP_MAX_STAMINA)
			override_cheat = false;
		return result;
	}

	void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo,
		bool isReliable, uint32_t reliableSeq) {
		static bool afterDash = false;

		// code...
		CALL_ORIGIN(LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook, __this, entityId, syncInfo, isReliable, reliableSeq);
	}

	void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state) {
		auto propType = static_cast<app::PropType__Enum>(type);
		bool isValid = OnPropertySet(propType);

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
