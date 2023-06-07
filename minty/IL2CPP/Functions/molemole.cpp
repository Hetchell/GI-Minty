#include "molemole.h"

namespace il2fns {
	void MoleMole__ActorUtils__ShowMessage(const char* message) {
		auto result = string_to_il2cppi(message);
		app::MoleMole__ActorUtils__ShowMessage(result);
	}
}