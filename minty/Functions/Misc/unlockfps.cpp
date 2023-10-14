#include "UnlockFPS.h"

namespace cheat {
	static void onUpdate_2(app::GameManager* __this, app::MethodInfo* method);

	UnlockFPS::UnlockFPS() {
		f_Enabled = config::getValue("functions:UnlockFPS", "enabled", false);
		f_Fps = config::getValue("functions:UnlockFPS", "value", 60);

		HookManager::install(app::GameManager_Update, onUpdate_2);
	}

	UnlockFPS& UnlockFPS::getInstance() {
		static UnlockFPS instance;
		return instance;
	}

	void UnlockFPS::GUI() {
		ConfigCheckbox("Unlock FPS", f_Enabled);
		ImGui::SameLine();
		HelpMarker(_("Unlocks framerate to target value."));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderInt(_("Target FPS"), f_Fps, 10, 360);
			unlockFPSHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void UnlockFPS::Outer() {
		if (unlockFPSHotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void UnlockFPS::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("Unlock FPS: %i"), f_Fps);
	}

	std::string UnlockFPS::getModule() {
		return _("Misc");
	}

	void onUpdate_2(app::GameManager* __this, app::MethodInfo* method) {
		auto& UnlockFPS = UnlockFPS::getInstance();
		bool enabled = UnlockFPS.f_Enabled.getValue();

		__try {
			app::UnityEngine__Application__set__targetFramerate(enabled ? UnlockFPS.f_Fps.getValue() : 60);
			app::UnityEngine__QualitySettings__set__vSyncCount(enabled ? 0 : 1);
		}
		__except (1) {
			util::log(M_Info, "lol");
		}

		CALL_ORIGIN(onUpdate_2, __this, method);
	}
}
