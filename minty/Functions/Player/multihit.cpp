#include "multihit.h"

static bool ifmh;
static bool ifinit;
static int quantityHit = 1;
static bool ifelem;

namespace cheat {
	static void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult);

	MultiHit::MultiHit() {
		HookManager::install(app::MoleMole_LCBaseCombat_FireBeingHitEvent, LCBaseCombat_FireBeingHitEvent_Hook);
	}

	void MultiHit::GUI() {
		ImGui::Checkbox("Multi-hit", &ifMultiHit);
		if (ifMultiHit) {
			ImGui::Indent();
			ImGui::SliderInt("Number of hits", &hitQuantity, 1, 50);
			ImGui::Checkbox("One-punch mode (overrides manual Multi-hit)", &ifOnepunch);
			ImGui::Unindent();
		}
	}

	static void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult)
	{
		if (ifmh && app::get_entityType(__this->fields._._._entity) == app::EntityType__Enum_1::Avatar) {
			for (int i = 0; i < MultiHit::ifOnepunch ? 1 : quantityHit; i++) { // 1 is hkjsamfduiewcmgrewrifntmryieuonfceruifnmer humhgrnmuyehrgnmy enemy hp / dmg
				CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
			}
		}
		else CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
	}
}
