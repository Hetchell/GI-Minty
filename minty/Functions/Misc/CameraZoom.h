#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class CameraZoom : public FN {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_CameraZoom;

		inline static Hotkey cameraZoomHotkey = Hotkey("CameraZoom");

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static CameraZoom& getInstance();

		CameraZoom();
	};
}
