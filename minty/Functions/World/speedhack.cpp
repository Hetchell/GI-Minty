#include "speedhack.h"

namespace cheat {
	void GameManager_Update_h(app::GameManager* __this);

	Speedhack::Speedhack() {
		HookManager::install(app::GameManager_Update, GameManager_Update_h);
		f_Speedhack = 2.f;
	}

	void Speedhack::GUI() {
		ImGui::Checkbox(_("Speedhack"), &ifSpeedhack);
		if (ifSpeedhack) {
			ImGui::Indent();
			ImGui::SliderFloat("Target speed", &f_Speedhack, 0, 10);
			speedHackHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void Speedhack::Outer() {
		if (speedHackHotkey.IsPressed()) {
			ifSpeedhack = !ifSpeedhack;
		}
	}

	void Speedhack::Status() {
		if (ifSpeedhack) {
			ImGui::Text(_("Speedhack (%.1f)"), f_Speedhack);
		}
	}

	void SetSpeed() {
		app::UnityEngine__set__Timescale(Speedhack::ifSpeedhack ? Speedhack::f_Speedhack : 1.f);
	}

	void GameManager_Update_h(app::GameManager* __this) {
		__try {
			SetSpeed();
		} __except (EXCEPTION_EXECUTE_HANDLER) {
			//util::log(M_Info, "Error!");
		}
		CALL_ORIGIN(GameManager_Update_h, __this);
	}
}