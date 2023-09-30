#include "unlockfps.h"

namespace cheat {
	UnlockFPS::UnlockFPS() {
		i_FPS = 60;
	}

	void UnlockFPS::GUI() {
		ImGui::Checkbox(_("Unlock FPS"), &ifUnlockFPS);
		ImGui::SameLine();
		HelpMarker(_("Unlocks framerate to target value."));
		if (ifUnlockFPS) {
			ImGui::Indent();
			if (ImGui::SliderInt(_("Target FPS"), &i_FPS, 10, 360))
				app::UnityEngine__Application__set__targetFramerate(i_FPS);

			ImGui::Unindent();
		}
		else {
			app::UnityEngine__Application__set__targetFramerate(60);
		}

		ImGui::Checkbox(_("Energy-saving mode"), &ifSavingMode);
		ImGui::SameLine();
		HelpMarker(_("Locks FPS to 5 when game is in background."));
		if (!app::UnityEngine__Application__get__isFocused() && ifSavingMode) {
			app::UnityEngine__Application__set__targetFramerate(5);
		}
	}

	void UnlockFPS::Outer() {
		if (unlockFPSHotkey.IsPressed())
			ifUnlockFPS = !ifUnlockFPS;
	}

	void UnlockFPS::Status() {
		if (ifUnlockFPS) {
			ImGui::Text("Unlock FPS: %i", i_FPS);
		}
	}
}