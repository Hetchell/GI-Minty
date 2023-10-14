#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class FovChanger : public FN {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_Fov;

		inline static Hotkey fovChangerHotkey = Hotkey("FovChanger");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static FovChanger& getInstance();

		FovChanger();
	};
}
