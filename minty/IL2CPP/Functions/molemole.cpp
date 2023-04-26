#include "molemole.h"

namespace function {
	LPVOID MoleMole__ActorUtils__ShowMessage__show(LPVOID __this, std::string message) {}

	bool MoleMole__ActorUtils__ShowMessage__show__FN() {
		HookManager::install(app::MoleMole__ActorUtils__ShowMessage, MoleMole__ActorUtils__ShowMessage__show);
	}
}