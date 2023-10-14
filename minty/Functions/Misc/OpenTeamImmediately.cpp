#include "OpenTeamImmediately.h"

namespace cheat {
	static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this);
	static void MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook(void* __this);
	static void MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook(void* __this);

	OpenTeamImmediately::OpenTeamImmediately() {
		f_Enabled = config::getValue("functions:OpenTeamImmediately", "enabled", false);

		HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook);
		HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_ClearView, MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook);
		HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_SetupView, MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook);
	}

	OpenTeamImmediately& OpenTeamImmediately::getInstance() {
		static OpenTeamImmediately instance;
		return instance;
	}

	void OpenTeamImmediately::GUI() {
		ConfigCheckbox("Open Team Immediately", f_Enabled);

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			otiHotkey.Draw();
			ImGui::Unindent();
		}
	}
	
	void OpenTeamImmediately::Outer() {
		if (otiHotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void OpenTeamImmediately::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("OTI");
	}

	std::string OpenTeamImmediately::getModule() {
		return _("Misc");
	}

	static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this) {
		auto& OpenTeamImmediately = OpenTeamImmediately::getInstance();

		if (OpenTeamImmediately.f_Enabled.getValue() && !OpenTeamImmediately.InLevelPlayerProfilePageContext)
			__this->fields._levelMainPageContext->fields._countDownTime = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
		return CALL_ORIGIN(MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook, __this);
	}

	static void MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook(void* __this) {
		auto& OpenTeamImmediately = OpenTeamImmediately::getInstance();

		OpenTeamImmediately.InLevelPlayerProfilePageContext = __this;
		CALL_ORIGIN(MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook, __this);
	}

	static void MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook(void* __this) {
		auto& OpenTeamImmediately = OpenTeamImmediately::getInstance();

		CALL_ORIGIN(MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook, __this);
		OpenTeamImmediately.InLevelPlayerProfilePageContext = nullptr;
	}
}
