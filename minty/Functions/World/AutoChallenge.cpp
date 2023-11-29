#include "AutoChallenge.h"

namespace cheat
{
	void onUpdate_7(app::GameManager* __this, app::MethodInfo* method);

	AutoChallenge::AutoChallenge() {
		f_Enabled = config::getValue("functions:AutoChallenge", "enabled", false);
		f_BombDestroy = config::getValue("functions:AutoChallenge", "bombDestroy", false);
		f_Range = config::getValue("functions:AutoChallenge", "range", 100.f);
		f_Delay = config::getValue("functions:AutoChallenge", "delay", 500);
		f_Hotkey = Hotkey("functions:AutoChallenge");

		HookManager::install(app::GameManager_Update, onUpdate_7);
	}

	AutoChallenge& AutoChallenge::getInstance()
	{
		static AutoChallenge instance;
		return instance;
	}

	void AutoChallenge::GUI()
	{
		ConfigCheckbox("Auto challenge", f_Enabled, _("Auto collect time challenge item"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat(_("Range"), f_Range, 0.f, 300.0f, _("Collect range."));
			ConfigSliderInt(_("Delay"), f_Delay, 0, 2000, _("Collect delay."));
			ConfigCheckbox("Destroy Bomb", f_BombDestroy, _("Auto destroy bombbarrel"));
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void AutoChallenge::Status()
	{
		if (f_Enabled.getValue())
			ImGui::Text("Challenge [%.01fm]", f_Range.getValue());
	}

	std::string AutoChallenge::getModule() {
		return _("World");
	}

	void AutoChallenge::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}
	
	void onUpdate_7(app::GameManager* __this, app::MethodInfo* method)
	{
		auto& autoChallenge = AutoChallenge::getInstance();
		auto currentTime = util::GetCurrentTimeMillisec();

		if (!autoChallenge.f_Enabled.getValue() || currentTime < autoChallenge.nextTime) {
			CALL_ORIGIN(onUpdate_7, __this, method);
			return;
		}

		auto& entityManager = game::EntityManager::getInstance();
		auto avatarEntity = entityManager.avatar();
		

		for (auto& entity : entityManager.entities(game::filters::puzzle::TimeTrialChallengeCollection))
		{

			if (avatarEntity->distance(entity) > autoChallenge.f_Range.getValue()) {
				continue;
			}

			auto combat = entity->combat();

			if (combat != nullptr)
			{

				if (entity->name().find("SkillObj_EmptyGadget") != std::string::npos)
				{
					auto combatProp = combat->fields._combatProperty_k__BackingField;
					auto maxHP = app::MoleMole_SafeFloat_get_Value(combatProp->fields.maxHP);

					// so many entities named "SkillObj_EmptyGadget", but the collection's hp is 99999.f
					if (maxHP > 99998 && maxHP < 99999.9)
					{
						entity->setRelativePosition(avatarEntity->relativePosition());
					}
				}
				else
				{
					entity->setRelativePosition(avatarEntity->relativePosition());
				}
			}
		}
		autoChallenge.nextTime = currentTime + autoChallenge.f_Delay.getValue();
		CALL_ORIGIN(onUpdate_7, __this, method);
	}
}