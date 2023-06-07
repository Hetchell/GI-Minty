#include "multihit.h"

static bool ifmh;
static bool ifinit;
static int quantityHit = 1;
static bool ifelem;

static void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult)
{
	//util::log(M_Info, "elem: %i", attackResult->fields._attackerAttackProperty->fields._elementType);
	if (ifelem) {
		//attackResult->fields._attackerAttackProperty->fields._elementType = app::ElementType__Enum::Electric;
	}
	//util::log(M_Info, "dmg: %f", attackResult->fields.damage);
	util::log(M_Info, "avatar: %i", app::get_entityType(__this->fields._._._entity));
	if (ifmh && app::get_entityType(__this->fields._._._entity) == app::EntityType__Enum_1::Avatar) {
		for (int i = 0; i < quantityHit; i++) {
			CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
		}
	} else CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
}

namespace il2fns {
	void MultiHit(bool value, int quantity) {
		if (!ifinit) {
			HookManager::install(app::MoleMole_LCBaseCombat_FireBeingHitEvent, LCBaseCombat_FireBeingHitEvent_Hook); ifinit = true;
		}
		ifmh = value;
		quantityHit = quantity;
	}
	void CustomElem(bool value) {
		ifelem = value;
	}
}