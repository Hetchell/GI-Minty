#include "infinitystamina.h"

void DataItem_HandleNormalProp_HookOn(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{

}

void DataItem_HandleNormalProp_HookOff(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{
	CALL_ORIGIN(DataItem_HandleNormalProp_HookOff, __this, type, value, state);
}

namespace il2fns {
	void Infinity_Stamina(bool value) {
		if (value)
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_HookOn);
		else
			HookManager::detach(DataItem_HandleNormalProp_HookOn);
			//HookManager::getOrigin(data)
			HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_HookOff);
	}
}