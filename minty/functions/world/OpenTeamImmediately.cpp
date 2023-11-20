#include "OpenTeamImmediately.h"

namespace cheat {
	static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this);
	static void MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook(void* __this);
	static void MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook(void* __this);

	OpenTeamImmediately::OpenTeamImmediately() {
		f_Enabled = config::getValue("functions:OpenTeamImmediately", "enabled", false);
		f_Hotkey = Hotkey("functions:OpenTeamImmediately");

		InLevelPlayerProfilePageContext = nullptr;

		HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook);
		HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_ClearView, MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook);
		HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_SetupView, MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook);
	}

	OpenTeamImmediately& OpenTeamImmediately::getInstance() {
		static OpenTeamImmediately instance;
		return instance;
	}

	void OpenTeamImmediately::GUI() {
		ConfigCheckbox("Open Team Immediately", f_Enabled, "Open team immediately without waiting for count down.");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}
	
	void OpenTeamImmediately::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void OpenTeamImmediately::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("OTI");
	}

	std::string OpenTeamImmediately::getModule() {
		return _("World");
	}

	static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this) {
		auto& openTeamImmediately = OpenTeamImmediately::getInstance();

		if (openTeamImmediately.f_Enabled.getValue() && !openTeamImmediately.InLevelPlayerProfilePageContext)
			app::MoleMole_InLevelMainPageContext_EndCountDown(__this->fields.__this);
		return CALL_ORIGIN(MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook, __this);
	}

	static void MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook(void* __this) {
		auto& openTeamImmediately = OpenTeamImmediately::getInstance();

		openTeamImmediately.InLevelPlayerProfilePageContext = __this;
		CALL_ORIGIN(MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook, __this);
	}

	static void MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook(void* __this) {
		auto& openTeamImmediately = OpenTeamImmediately::getInstance();

		CALL_ORIGIN(MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook, __this);
		openTeamImmediately.InLevelPlayerProfilePageContext = nullptr;
	}
}
