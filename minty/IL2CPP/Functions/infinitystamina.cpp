#include "infinitystamina.h"

static bool ifstam;
static bool ifinit;

void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{
	if (!ifstam)
		CALL_ORIGIN(DataItem_HandleNormalProp_Hook, __this, type, value, state);
}

void VCHumanoidMove_Scara_Hook(app::VCHumanoidMove* __this, float somevalue)
{
	if (ifstam)
		somevalue = 34028234663852885981170418348451692544.f;
	CALL_ORIGIN(VCHumanoidMove_Scara_Hook, __this, somevalue);
}

namespace il2fns {
	void Infinity_Stamina(bool value) {
		if (!ifinit) {
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_Hook);
			HookManager::install(app::VCHumanoidMove_Scara, VCHumanoidMove_Scara_Hook); ifinit = true;
		}
		ifstam = value;
	}
}