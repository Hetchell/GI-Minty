#include "molemole.h"

namespace il2fns {
	void MoleMole__ActorUtils__ShowMessage(const char* message) {
		void* result = app::il2cpp_string_new(message);
		app::MoleMole__ActorUtils__ShowMessage(result);
	}
}