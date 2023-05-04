#include "unlockfps.h"

namespace il2fns {
	void UnityEngine__Application__set_targetFramerate(int value) {
		app::UnityEngine__set__Timescale(value);
	}
}