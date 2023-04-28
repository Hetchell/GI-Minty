#include "molemole.h"

namespace il2fns {
	//LPVOID MoleMole__ActorUtils__ShowMessage__show(LPVOID __this, std::string message) {}

	LPVOID MoleMole__ActorUtils__ShowMessage(LPVOID __this, LPVOID message) {
		message = app::il2cpp_string_new("wtf minty!!!!! 123123");
		CALL_ORIGIN(MoleMole__ActorUtils__ShowMessage, __this, message);
		return nullptr;
	}
	void MoleMole__ActorUtils__ShowMessage_I() {
		//LPVOID __this = nullptr;
		HookManager::install(app::MoleMole__ActorUtils__ShowMessage, MoleMole__ActorUtils__ShowMessage);
		//MoleMole__ActorUtils__ShowMessage__show(__this, app::il2cpp_string_new(message));
	}
}