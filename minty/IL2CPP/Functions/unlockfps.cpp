#include "unlockfps.h"

namespace il2fns {
	void UnityEngine__Application__set_targetFramerate(int32_t value) {
		app::UnityEngine__Application__set__targetFramerate(value);
		app::UnityEngine__QualitySettings__set__vSyncCount(0);
	}
}