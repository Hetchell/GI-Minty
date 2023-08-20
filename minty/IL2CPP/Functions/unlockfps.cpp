#include "unlockfps.h"

namespace il2fns {
	void UnlockFps() {
		static bool ifunlock;
		static bool ifsave;
		static int target = 60;
		if (ImGui::Checkbox("Unlock FPS", &ifunlock))
			if (!ifunlock)
				app::UnityEngine__Application__set__targetFramerate(60); /*app::UnityEngine__QualitySettings__set__vSyncCount(1);*/
		ImGui::SameLine();
		HelpMarker("Unlocks framerate to target value.");
		if (ifunlock) {
			app::UnityEngine__QualitySettings__set__vSyncCount(0);
			ImGui::Indent();
			if (ImGui::SliderInt("Target FPS", &target, 10, 360))
				app::UnityEngine__Application__set__targetFramerate(target); 
			ImGui::Unindent();
		}
		ImGui::Checkbox("Energy-saving mode", &ifsave);
		ImGui::SameLine();
		HelpMarker("Locks FPS to 5 when game is in background.");
		if (!app::UnityEngine__Application__get__isFocused() && ifsave) {
			app::UnityEngine__Application__set__targetFramerate(5);
		}
	}
}