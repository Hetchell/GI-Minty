#include "GameSpeed.h"

namespace cheat {
	void onUpdate_3(app::GameManager* __this, app::MethodInfo* method);

	GameSpeed::GameSpeed() {
		f_Enabled = config::getValue("functions:GameSpeed", "enabled", false);
		f_Speed = config::getValue("functions:GameSpeed", "multiplier", 5.0f);
		f_Hotkey = Hotkey("functions:GameSpeed");

		HookManager::install(app::GameManager_Update, onUpdate_3);
	}

	GameSpeed& GameSpeed::getInstance() {
		static GameSpeed instance;
		return instance;
	}

	void GameSpeed::GUI() {
		ConfigCheckbox("Game Speed", f_Enabled, "Speeds up game.");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat("Multiplier", f_Speed, 1.0f, 20.0f, "Set GameSpeed Multiplier");
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void GameSpeed::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void GameSpeed::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("GameSpeed (%.1f)"), f_Speed.getValue());
	}

	std::string GameSpeed::getModule() {
		return _("World");
	}

	void onUpdate_3(app::GameManager* __this, app::MethodInfo* method) {
		auto& GameSpeed = GameSpeed::getInstance();

		app::Time_set_timeScale(GameSpeed.f_Enabled.getValue() ? GameSpeed.f_Speed.getValue() : 1.0f);
		CALL_ORIGIN(onUpdate_3, __this, method);
	}
}
