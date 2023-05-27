#include "unlockfps.h"

namespace il2fns {
	void UnityEngine__Application__set_targetFramerate(int32_t value) {
		try {
			if (app::UnityEngine__Application__get__isFocused()) {
				//util::log(M_Info, "focus on");
				app::UnityEngine__Application__set__targetFramerate(value);
				app::UnityEngine__QualitySettings__set__vSyncCount(0);
			}
			else {
				//util::log(M_Info, "focus off");
				app::UnityEngine__Application__set__targetFramerate(5);
			}
		}
		catch (...) {}
	}
}