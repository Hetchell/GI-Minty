#include "multihit.h"

namespace cheat {
	static void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult);
	static app::LCBaseCombat* lcbc;
	static uint32_t attackee;
	static app::AttackResult* ar;
	MultiHit::MultiHit() {
		HookManager::install(app::MoleMole_LCBaseCombat_FireBeingHitEvent, LCBaseCombat_FireBeingHitEvent_Hook);
	}

	void MultiHit::GUI() {
		ImGui::Checkbox("Multi-hit", &ifMultiHit);
		if (ifMultiHit) {
			ImGui::Indent();
			ImGui::SliderInt("Number of hits", &hitQuantity, 1, 50);
			//ImGui::Checkbox("One-punch mode (overrides manual Multi-hit)", &ifOnepunch);
			multiHitHotkey.Draw();
			ImGui::Unindent();
		}

		if (ImGui::Button("imitate")) {
			//CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, lcbc, attackee, ar);
			//app::MoleMole_LCBaseCombat_FireBeingHitEvent(lcbc, attackee, ar);
			app::DoHitEntity(attackee, ar, true);
		}
		if (lcbc && attackee && ar) {
			ImGui::Text("attackee: %i", attackee);
			ImGui::Text("rid: %i", lcbc->fields._attackTarget.runtimeID);
			ImGui::Text("rid2: %i", lcbc->fields._._._entity->fields._runtimeID_k__BackingField);
		}
	}

	void MultiHit::Outer() {
		if (multiHitHotkey.IsPressed()) {
			ifMultiHit = !ifMultiHit;
		}
	}

	void MultiHit::Status() {
		if (ifMultiHit) {
			ImGui::Text("Multi-hit (%s)", ifOnepunch ? std::string("One-punch") : std::string(hitQuantity + " hits"));
		}
	}

	static void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult)
	{
		//util::log(M_Info, "maxhp defense: %i", attackResult->fields.defenseCombatProperty->fields.HP._data1);
		if (MultiHit::ifMultiHit && app::get_entityType(__this->fields._._._entity) == app::EntityType__Enum_1::Avatar) {
			lcbc = __this;
			attackee = attackeeRuntimeID;
			ar = attackResult;
			//for (int i = 0; i < MultiHit::ifOnepunch ? 1 : MultiHit::hitQuantity; i++) { // 1 is enemy hp / dmg
			//	CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
			//}
			for (int i = 0; i < MultiHit::hitQuantity; i++) { // 1 is enemy hp / dmg
				CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
			}
		}
		else CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
	}
}
