#include "GameSpeed.h"

namespace cheat {
	void onUpdate_3(app::GameManager* __this, app::MethodInfo* methodInfo);

	GameSpeed::GameSpeed() {
		f_Enabled = config::getValue("functions:GameSpeed", "enabled", false);
		f_Speed = config::getValue("functions:GameSpeed", "speed" , 2.0f);

		HookManager::install(app::GameManager_Update, onUpdate_3);
	}

	GameSpeed& GameSpeed::getInstance() {
		static GameSpeed instance;
		return instance;
	}

	void GameSpeed::GUI() {
		ConfigCheckbox(_("GameSpeed"), f_Enabled);

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat("Speed value", f_Speed, 0.0f, 10.0f);
			speedHackHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void GameSpeed::Outer() {
		if (speedHackHotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void GameSpeed::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("GameSpeed (%.1f)"), f_Speed.getValue());
	}

	std::string GameSpeed::getModule() {
		return _("World");
	}

	void changeGameSpeed() {
		auto& GameSpeed = GameSpeed::getInstance();

		app::UnityEngine__set__Timescale(GameSpeed.f_Enabled.getValue() ? GameSpeed.f_Speed.getValue() : 1.0f);
	}

	void onUpdate_3(app::GameManager* __this, app::MethodInfo* methodInfo) {
		__try {
			changeGameSpeed();
		} __except (1) {}

		CALL_ORIGIN(onUpdate_3, __this, methodInfo);
	}
}
