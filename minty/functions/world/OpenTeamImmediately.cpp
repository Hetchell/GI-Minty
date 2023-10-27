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
		ConfigCheckbox("Open Team Immediately", f_Enabled);

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
		auto& OpenTeamImmediately = OpenTeamImmediately::getInstance();

		if (OpenTeamImmediately.f_Enabled.getValue() && !OpenTeamImmediately.InLevelPlayerProfilePageContext) {
			__this->fields._levelMainPageContext->fields.LBENNACEFMN = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.EIKHAEMJIIN = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.BEMNEGGOOAJ = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.KLGJDCPGLKL = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.GBCCEOBJOMO = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.PNONLMKONHN = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.KJCGOMNIEOM = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.KJCGOMNIEOM = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.NMNOKLKCLBD_k__BackingField = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.PNHDLHHINJP_k__BackingField = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.IMJOJMPCECK_k__BackingField = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.EMJGCLKKODO = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.GPIEGIOKFDB = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.OHANLENNCBK = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.LLBIKOPGGMI = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.LFMONKCFECA = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.CJGHFCAFNAK = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.MAHPMFPBMLN = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.INKOBGEGJDO = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.FDKENNLAOEM = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.DJENJPHNCAK = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.OMDENNKLIGB = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.DMIDIKDLGCC = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			__this->fields._levelMainPageContext->fields.HCCKIJEIKGM = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
			std::cout << "----------" << "\n";
			std::cout << "LBENNACEFMN: " << __this->fields._levelMainPageContext->fields.LBENNACEFMN << "\n";
			std::cout << "EIKHAEMJIIN: " << __this->fields._levelMainPageContext->fields.EIKHAEMJIIN << "\n";
			std::cout << "BEMNEGGOOAJ: " << __this->fields._levelMainPageContext->fields.BEMNEGGOOAJ << "\n";
			//std::cout << "KLGJDCPGLKL: " << __this->fields._levelMainPageContext->fields.KLGJDCPGLKL << "\n";
			std::cout << "GBCCEOBJOMO: " << __this->fields._levelMainPageContext->fields.GBCCEOBJOMO << "\n";
			//std::cout << "PNONLMKONHN: " << __this->fields._levelMainPageContext->fields.PNONLMKONHN << "\n";
			//std::cout << "KJCGOMNIEOM: " << __this->fields._levelMainPageContext->fields.KJCGOMNIEOM << "\n";
			//std::cout << "NMNOKLKCLBD_k__BackingField: " << __this->fields._levelMainPageContext->fields.NMNOKLKCLBD_k__BackingField << "\n";
			//std::cout << "PNHDLHHINJP_k__BackingField: " << __this->fields._levelMainPageContext->fields.PNHDLHHINJP_k__BackingField << "\n";
			//std::cout << "IMJOJMPCECK_k__BackingField: " << __this->fields._levelMainPageContext->fields.IMJOJMPCECK_k__BackingField << "\n";
			//std::cout << "EMJGCLKKODO: " << __this->fields._levelMainPageContext->fields.EMJGCLKKODO << "\n";
			std::cout << "GPIEGIOKFDB: " << __this->fields._levelMainPageContext->fields.GPIEGIOKFDB << "\n";
			std::cout << "OHANLENNCBK: " << __this->fields._levelMainPageContext->fields.OHANLENNCBK << "\n";
			std::cout << "EnterCountDown: " << __this->fields._levelMainPageContext->fields.EnterCountDown << "\n";
			std::cout << "LLBIKOPGGMI: " << __this->fields._levelMainPageContext->fields.LLBIKOPGGMI << "\n";
			std::cout << "LFMONKCFECA: " << __this->fields._levelMainPageContext->fields.LFMONKCFECA << "\n";
			std::cout << "CJGHFCAFNAK: " << __this->fields._levelMainPageContext->fields.CJGHFCAFNAK << "\n";
			//std::cout << "MAHPMFPBMLN: " << __this->fields._levelMainPageContext->fields.MAHPMFPBMLN << "\n";
			//std::cout << "INKOBGEGJDO: " << __this->fields._levelMainPageContext->fields.INKOBGEGJDO << "\n";
			//std::cout << "FDKENNLAOEM: " << __this->fields._levelMainPageContext->fields.FDKENNLAOEM << "\n";
			//std::cout << "DJENJPHNCAK: " << __this->fields._levelMainPageContext->fields.DJENJPHNCAK << "\n";
			std::cout << "OMDENNKLIGB: " << __this->fields._levelMainPageContext->fields.OMDENNKLIGB << "\n";
			//std::cout << "DMIDIKDLGCC: " << __this->fields._levelMainPageContext->fields.DMIDIKDLGCC << "\n";
			std::cout << "HCCKIJEIKGM: " << __this->fields._levelMainPageContext->fields.HCCKIJEIKGM << "\n";
			std::cout << "----------" << "\n";
			//__this->fields._levelMainPageContext->fields._countDownTime = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
		}
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
