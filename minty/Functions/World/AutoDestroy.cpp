#include "AutoDestroy.h"
#include "AutoChallenge.h"

namespace cheat
{
	static void LCAbilityElement_ReduceModifierDurability_Hook(app::LCAbilityElement* __this, int32_t modifierDurabilityIndex, float reduceDurability, app::Nullable_1_Single_ deltaTime, app::MethodInfo* method);

	AutoDestroy::AutoDestroy() {
		f_Enabled = config::getValue("functions:AutoDestroy", "enabled", false);
		f_Range = config::getValue("functions:AutoDestroy", "range", 10.f);
		f_Hotkey = Hotkey("functions:AutoDestroy");

		f_DestroyOres = config::getValue("functions:AutoDestroy", "DestroyOres", false);
		f_DestroyShields = config::getValue("functions:AutoDestroy", "DestroyShields", false);
		f_DestroyDoodads = config::getValue("functions:AutoDestroy", "DestroyDoodads", false);
		f_DestroyPlants = config::getValue("functions:AutoDestroy", "DestroyPlants", false);
		f_DestroySpecialObjects = config::getValue("functions:AutoDestroy", "DestroySpecialObjects", false);
		f_DestroySpecialChests = config::getValue("functions:AutoDestroy", "DestroySpecialChests", false);

		HookManager::install(app::MoleMole_LCAbilityElement_ReduceModifierDurability, LCAbilityElement_ReduceModifierDurability_Hook);
	}

	AutoDestroy& AutoDestroy::getInstance()
	{
		static AutoDestroy instance;
		return instance;
	}

	void AutoDestroy::GUI()
	{
		ConfigCheckbox("AutoDestroy", f_Enabled, "Instantly destroys non-living objects within range.");
		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigCheckbox("Ores", f_DestroyOres, "Ores and variants, e.g. electro crystals, marrows, etc.");
			ConfigCheckbox("Shields", f_DestroyShields, "Abyss mage/churl/slime shields.");
			ConfigCheckbox("Doodads", f_DestroyDoodads, "Barrels, boxes, vases, etc.");
			ConfigCheckbox("Plants", f_DestroyPlants, "Dandelion Seeds, Sakura Bloom, etc.");
			ConfigCheckbox("Special Objects", f_DestroySpecialObjects, "Destroy Ancient Rime, Large and Small Rock Piles");
			ConfigCheckbox("Special Chests", f_DestroySpecialChests, "Destroy Chests with Brambles, Frozen, or In Rocks");
			ImGui::Unindent();
			ConfigSliderFloat("Range (m)", f_Range, 0.1f, 15.0f);
		}
	}

	void AutoDestroy::Status()
	{
		if (f_Enabled.getValue())
			ImGui::Text("Challenge [%.01fm]", f_Range.getValue());
	}

	std::string AutoDestroy::getModule() {
		return _("World");
	}

	static void LCAbilityElement_ReduceModifierDurability_Hook(app::LCAbilityElement* __this, int32_t modifierDurabilityIndex, float reduceDurability, app::Nullable_1_Single_ deltaTime, app::MethodInfo* method)
	{
		auto& manager = game::EntityManager::getInstance();
		auto& autoDestroy = AutoDestroy::getInstance();
		auto entity = __this->fields._._._entity;
		auto autoChallenge = AutoChallenge::getInstance();
		if (autoChallenge.f_Enabled.getValue() && autoChallenge.f_BombDestroy.getValue() &&
			autoChallenge.f_Range.getValue() > manager.avatar()->distance(entity) &&
			game::filters::puzzle::Bombbarrel.IsValid(manager.entity(entity))
			)
		{
			reduceDurability = 1000.f;
		}
		if (autoDestroy.f_Enabled.getValue() &&
			autoDestroy.f_Range.getValue() > manager.avatar()->distance(entity) &&
			(
				(autoDestroy.f_DestroyOres.getValue() && game::filters::combined::Ores.IsValid(manager.entity(entity))) ||
				(autoDestroy.f_DestroyDoodads.getValue() && (game::filters::combined::Doodads.IsValid(manager.entity(entity)) || game::filters::chest::SBramble.IsValid(manager.entity(entity)))) ||
				(autoDestroy.f_DestroyShields.getValue() && !game::filters::combined::MonsterBosses.IsValid(manager.entity(entity)) && (
					game::filters::combined::MonsterShielded.IsValid(manager.entity(entity)) ||											// For shields attached to monsters, e.g. abyss mage shields.
					game::filters::combined::MonsterEquips.IsValid(manager.entity(entity)))) ||											// For shields/weapons equipped by monsters, e.g. rock shield.
				(autoDestroy.f_DestroyPlants.getValue() && game::filters::combined::PlantDestroy.IsValid(manager.entity(entity))) ||			// For plants e.g dandelion seeds.
				(autoDestroy.f_DestroySpecialObjects.getValue() && game::filters::combined::BreakableObjects.IsValid(manager.entity(entity))) ||	// For Breakable Objects e.g Ancient Rime, Large and Small Rock Piles.
				(autoDestroy.f_DestroySpecialChests.getValue() && game::filters::combined::Chests.IsValid(manager.entity(entity)))					// For Special Chests e.g Brambles, Frozen, Encased in Rock.
				)
			)
		{
			reduceDurability = 1000;
		}
		CALL_ORIGIN(LCAbilityElement_ReduceModifierDurability_Hook, __this, modifierDurabilityIndex, reduceDurability, deltaTime, method);
	}


	void AutoDestroy::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

}