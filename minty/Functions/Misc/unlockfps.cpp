#include "unlockfps.h"

namespace cheat {
	void GameManager_UpdateH(app::GameManager* __this);

	UnlockFPS::UnlockFPS() {
		i_FPS = 60;
		ifUnlockFPS = config::getValue("functions", "UnlockFPS", false);
		HookManager::install(app::GameManager_Update, GameManager_UpdateH);
	}

	void UnlockFPS::GUI() {
		CheckBoxFN("Unlock FPS", ifUnlockFPS, "UnlockFPS")
		ImGui::SameLine();
		HelpMarker(_("Unlocks framerate to target value."));
		if (ifUnlockFPS) {
			ImGui::Indent();
			ImGui::SliderInt(_("Target FPS"), &i_FPS, 10, 360);
			unlockFPSHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void UnlockFPS::Outer() {
		if (unlockFPSHotkey.IsPressed())
			ifUnlockFPS = !ifUnlockFPS;
	}

	void UnlockFPS::Status() {
		if (ifUnlockFPS) {
			ImGui::Text(_("Unlock FPS: %i"), i_FPS);
		}
	}

	void GameManager_UpdateH(app::GameManager* __this) {
		__try {
			app::UnityEngine__Application__set__targetFramerate(UnlockFPS::ifUnlockFPS ? UnlockFPS::i_FPS : 60);
			app::UnityEngine__QualitySettings__set__vSyncCount(UnlockFPS::ifUnlockFPS ? 0 : 1);
		}
		__except (1) {
			util::log(M_Info, "lol");
		}
		CALL_ORIGIN(GameManager_UpdateH, __this);
	}
}