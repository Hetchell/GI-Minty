#include "infinitystamina.h"

static bool ifstam;
static bool ifinit;

bool OnPropertySet(app::PropType__Enum propType)
{
	using PT = app::PropType__Enum;
	static bool override_cheat = true;

	if (propType == PT::PROP_CUR_TEMPORARY_STAMINA)
		override_cheat = true;

	const bool result = !ifstam ||
		(propType != PT::PROP_MAX_STAMINA &&
			propType != PT::PROP_CUR_PERSIST_STAMINA &&
			propType != PT::PROP_CUR_TEMPORARY_STAMINA);

	if (propType == PT::PROP_MAX_STAMINA)
		override_cheat = false;

	return result;
}

void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{
	auto propType = static_cast<app::PropType__Enum>(type);
	bool isValid = OnPropertySet(propType);
	if (isValid)
		CALL_ORIGIN(DataItem_HandleNormalProp_Hook, __this, type, value, state);
}

void VCHumanoidMove_Scara_Hook(app::VCHumanoidMove* __this, float somevalue)
{
	if (ifstam)
		somevalue = 34028234663852885981170418348451692544.f;
	CALL_ORIGIN(VCHumanoidMove_Scara_Hook, __this, somevalue);
}

namespace il2fns {
	void Infinity_Stamina() {
		while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinit) {
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_Hook);
			HookManager::install(app::VCHumanoidMove_Scara, VCHumanoidMove_Scara_Hook); ifinit = true;
		}

		ifstam = readBoolFuncStateFromJson("InfStamina");

		if (ImGui::Checkbox("Infinity stamina", &ifstam)) {
			saveFuncStateToJson("InfStamina", ifstam);
		}
		ImGui::SameLine();
		HelpMarker("Prevents stamina level from changing.");
	}
}