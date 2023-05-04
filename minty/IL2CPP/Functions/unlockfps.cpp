#include "unlockfps.h"

namespace il2fns {
	void UnityEngine__Application__set_targetFramerate(int value) {
		app::UnityEngine__Application__set__targetFramerate(il2cpp_string_new(std::to_string(value).c_str()));
	}
}