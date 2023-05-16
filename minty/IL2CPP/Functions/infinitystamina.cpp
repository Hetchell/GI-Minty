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

namespace il2fns {
	void Infinity_Stamina(bool value) {
		if (value) {
			//if (ifvalue = false)
				//HookManager::detach(DataItem_HandleNormalProp_HookOff);
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_HookOn);
		}
		else {
			//if (ifvalue = true)
				//HookManager::detach(DataItem_HandleNormalProp_HookOn);
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_HookOff);
		}
	}
}