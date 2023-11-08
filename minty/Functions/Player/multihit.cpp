#include "MultiHit.h"

namespace cheat {
	static void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult);

	MultiHit::MultiHit() {
		f_Enabled = config::getValue("functions:MultiHit", "enabled", false);
		f_Hits = config::getValue("functions:MultiHit", "hits", 1);
		f_Hotkey = Hotkey("functions:MultiHit");

		HookManager::install(app::MoleMole_LCBaseCombat_FireBeingHitEvent, LCBaseCombat_FireBeingHitEvent_Hook);
	}

	MultiHit& MultiHit::getInstance() {
		static MultiHit instance;
		return instance;
	}

	void MultiHit::GUI() {
		ConfigCheckbox("Multi Hit", f_Enabled);

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderInt("Hits", f_Hits, 1, 1000);
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void MultiHit::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void MultiHit::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("MultiHit (%i)", f_Hits.getValue());
	}
	
	std::string MultiHit::getModule() {
		return _("Player");
	}

	void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult) {
		auto& multiHit = MultiHit::getInstance();

		if (multiHit.f_Enabled.getValue() && app::MoleMole_BaseEntity_get_entityType(__this->fields._._._entity) == app::EntityType__Enum_1::Avatar) {
			for (int i = 0; i < multiHit.f_Hits.getValue(); i++)
				CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
		} else 
			CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
	}
}
