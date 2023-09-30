#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"

namespace cheat {
	class UnlockFPS : public FN {
	public:
		inline static bool ifUnlockFPS;
		inline static int i_FPS;

		void GUI() override;
		void Outer() override;
		void Status() override;

		UnlockFPS();
	};
}

namespace il2fns {
	void UnlockFps();
}