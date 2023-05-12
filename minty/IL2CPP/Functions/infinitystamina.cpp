#include "infinitystamina.h"

//bool OnPropertySet(app::PropType__Enum propType)
//{
//	bool bruh = false;
//
//	using PT = app::PropType__Enum;
//	static bool override_cheat = true;
//
//	if (propType == PT::PROP_CUR_TEMPORARY_STAMINA)
//		override_cheat = true;
//
//	const bool result = true || bruh || override_cheat ||
//		(propType != PT::PROP_MAX_STAMINA &&
//			propType != PT::PROP_CUR_PERSIST_STAMINA &&
//			propType != PT::PROP_CUR_TEMPORARY_STAMINA);
//
//	if (propType == PT::PROP_MAX_STAMINA)
//		override_cheat = false;
//
//	util::log(2, "result: %d", result);
//
//	return result;
//}

void DataItem_HandleNormalProp_HookOn(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{
	/*auto propType = static_cast<app::PropType__Enum>(type);
	bool isValid = OnPropertySet(propType);*/
	//if (isValid)
		//CALL_ORIGIN(DataItem_HandleNormalProp_Hook, __this, type, value, state);
}

void DataItem_HandleNormalProp_HookOff(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state)
{
	if (true)
	
	/*auto propType = static_cast<app::PropType__Enum>(type);
	bool isValid = OnPropertySet(propType);*/
	//if (isValid)
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