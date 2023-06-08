#include "unlockfps.h"

namespace il2fns {
	void UnityEngine__Application__set_targetFramerate(int32_t value) {
		if (app::UnityEngine__Application__get__isFocused()) {
			app::UnityEngine__Application__set__targetFramerate(value);
			app::UnityEngine__QualitySettings__set__vSyncCount(0);
		}
		else {
			app::UnityEngine__Application__set__targetFramerate(5);
		}
	}
}