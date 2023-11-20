#include "UnlockFPS.h"

namespace cheat {
	static void onUpdate_2(app::GameManager* __this, app::MethodInfo* method);

	UnlockFPS::UnlockFPS() {
		f_Enabled = config::getValue("functions:UnlockFPS", "enabled", false);
		f_EnabledLimit = config::getValue("functions:UnlockFPS:Limit", "enabled", false);
		f_Fps = config::getValue("functions:UnlockFPS", "value", 60);
		f_FpsLimit = config::getValue("functions:UnlockFPS:Limit", "value", 60);
		f_Hotkey = Hotkey("functions:UnlockFPS");

		HookManager::install(app::GameManager_Update, onUpdate_2);
	}

	UnlockFPS& UnlockFPS::getInstance() {
		static UnlockFPS instance;
		return instance;
	}

	void UnlockFPS::GUI() {
		ConfigCheckbox("Unlock FPS", f_Enabled, "Unlocks higher framerate.");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderInt(_("FPS"), f_Fps, 1, 360);
			ConfigCheckbox("Lock FPS", f_EnabledLimit, "Limit framerate while the game window isn't focused.\n"
				"This won't work if the cheat menu is open or if you're in a loading screen.");

			if (f_EnabledLimit.getValue())
				ConfigSliderInt(_("FPS Limit"), f_FpsLimit, 1, 360);

			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void UnlockFPS::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void UnlockFPS::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("Unlock FPS: %i"), f_Fps);
	}

	std::string UnlockFPS::getModule() {
		return _("Visuals");
	}

	void onUpdate_2(app::GameManager* __this, app::MethodInfo* method) {
		auto& unlockFPS = UnlockFPS::getInstance();
		bool enabled = unlockFPS.f_Enabled.getValue();
		int fps = unlockFPS.f_Fps.getValue();

		app::Application_set_targetFrameRate(enabled ? fps : 60);
		app::QualitySettings_set_vSyncCount(enabled ? 0 : 1);

		if (enabled) {
			if (!unlockFPS.f_EnabledLimit.getValue())
				app::Application_set_targetFrameRate(fps);
			else {
				if (!app::Application_get_isFocused())
					app::Application_set_targetFrameRate(unlockFPS.f_FpsLimit.getValue());
				else
					app::Application_set_targetFrameRate(fps);
			}
		}

		CALL_ORIGIN(onUpdate_2, __this, method);
	}
}
