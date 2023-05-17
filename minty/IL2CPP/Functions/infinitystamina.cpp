#include "infinitystamina.h"

static bool ifvalue;
void DataItem_HandleNormalProp_HookOn(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{
	ifvalue = true;
}

void DataItem_HandleNormalProp_HookOff(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{
	ifvalue = false;
	CALL_ORIGIN(DataItem_HandleNormalProp_HookOff, __this, type, value, state);
}

void VCHumanoidMove_Scara_HookOn(app::VCHumanoidMove* __this, float somevalue)
{
	somevalue = 34028234663852885981170418348451692544.f;
	CALL_ORIGIN(VCHumanoidMove_Scara_HookOn, __this, somevalue);
}

void VCHumanoidMove_Scara_HookOff(app::VCHumanoidMove* __this, float somevalue)
{
	CALL_ORIGIN(VCHumanoidMove_Scara_HookOff, __this, somevalue);
}

namespace il2fns {
	void Infinity_Stamina(bool value) {
		if (value) {
			//if (ifvalue = false)
				//HookManager::detach(DataItem_HandleNormalProp_HookOff);
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_HookOn);
			HookManager::install(app::VCHumanoidMove_Scara, VCHumanoidMove_Scara_HookOn);
		}
		else {
			//if (ifvalue = true)
			HookManager::detach(DataItem_HandleNormalProp_HookOn);
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_HookOff);
			HookManager::detach(VCHumanoidMove_Scara_HookOn);
			HookManager::install(app::VCHumanoidMove_Scara, VCHumanoidMove_Scara_HookOff);
		}
	}
}