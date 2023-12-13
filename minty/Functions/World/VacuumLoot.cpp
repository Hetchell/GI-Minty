#include "VacuumLoot.h"

namespace cheat
{
	void onUpdate_8(app::GameManager* __this, app::MethodInfo* method);

	VacuumLoot::VacuumLoot() {
		f_Enabled = config::getValue("functions:VacuumLoot", "enabled", false);
		f_Delay = config::getValue("functions:VacuumLoot", "delay", 1000);
		f_Distance = config::getValue("functions:VacuumLoot", "distance", 1.5f);
		f_Radius = config::getValue("functions:VacuumLoot", "radius", 20.f);
		f_Hotkey = Hotkey("functions:VacuumLoot");

		f_Ores = config::getValue("functions:VacuumLoot", "ores", false);
		f_OresDrop = config::getValue("functions:VacuumLoot", "oresDrop", false);
		f_Oculies = config::getValue("functions:VacuumLoot", "oculies", false);
		f_Plants = config::getValue("functions:VacuumLoot", "plants", false);
		f_Equipments = config::getValue("functions:VacuumLoot", "equipments", false);
		f_ItemDrops = config::getValue("functions:VacuumLoot", "itemDrops", false);

		HookManager::install(app::GameManager_Update, onUpdate_8);
	}

	VacuumLoot& VacuumLoot::getInstance()
	{
		static VacuumLoot instance;
		return instance;
	}

	void VacuumLoot::GUI()
	{
		ConfigCheckbox("Vacuum loot", f_Enabled, "Vacuum of various entities to the character"); 
		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderInt("Delay Time (ms)", f_Delay, 1, 1000, "Delay (in ms) between loot vacuum.");
			ConfigSliderFloat("Radius (m)", f_Radius, 0.1f, 100.0f, "Radius of common loot vacuum.");
			ConfigSliderFloat("Distance (m)", f_Distance, 0.1f, 10.0f, "Distance between the player and the loot.\n"
				"Values under 1.5 may be too intruding.");

			if (ImGui::BeginCombo("Select the loot to be picked up.", "Filters")) {
				ConfigCheckbox("Ores", f_Ores);
				ConfigCheckbox("Ores drop", f_OresDrop);
				ConfigCheckbox("Oculies", f_Oculies, "All types of oculies");
				ConfigCheckbox("Plants", f_Plants);
				ConfigCheckbox("Equipments", f_Equipments, "Artifacts, swords, claymores etc.");
				ConfigCheckbox("Mob loot", f_ItemDrops);

				ImGui::EndCombo();
			}

			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void VacuumLoot::Status()
	{
		if (f_Enabled.getValue())
			ImGui::Text("VacuumLoot\n[%dms|%.01fm|%.01fm]",
				f_Delay.getValue(),
				f_Radius.getValue(),
				f_Distance.getValue()
			);
	}

	std::string VacuumLoot::getModule() {
		return _("World");	
	}

	void VacuumLoot::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void onUpdate_8(app::GameManager* __this, app::MethodInfo* method)
	{
		auto currentTime = util::GetCurrentTimeMillisec();
		auto vacuumLoot = VacuumLoot::getInstance();
		if (currentTime < vacuumLoot.nextTime || !vacuumLoot.f_Enabled.getValue()) {
			CALL_ORIGIN(onUpdate_8, __this, method);
			return;
		}

		auto& manager = game::EntityManager::getInstance();
		auto avatarEntity = manager.avatar();

		for (const auto& entity : manager.entities())
		{
			if (!(
				(vacuumLoot.f_Ores.getValue() && game::filters::combined::Ores.IsValid(entity)) ||
				(vacuumLoot.f_OresDrop.getValue() && game::filters::combined::OresDrop.IsValid(entity)) ||
				(vacuumLoot.f_Oculies.getValue() && game::filters::combined::Oculies.IsValid(entity)) ||
				(vacuumLoot.f_Plants.getValue() && game::filters::combined::Plants.IsValid(entity)) ||
				(vacuumLoot.f_Equipments.getValue() && game::filters::combined::Equipments.IsValid(entity)) ||
				(vacuumLoot.f_ItemDrops.getValue() && game::filters::featured::ItemDrops.IsValid(entity))
			)) 
				continue;

			auto distance = manager.avatar()->distance(entity);
			
			if (distance <= vacuumLoot.f_Radius.getValue()) {

				entity->setRelativePosition(avatarEntity->relativePosition() + avatarEntity->forward() * vacuumLoot.f_Distance.getValue());
			}
		}
		vacuumLoot.nextTime = currentTime + vacuumLoot.f_Delay.getValue();

		CALL_ORIGIN(onUpdate_8, __this, method);
	}
}