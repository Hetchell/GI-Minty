#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class CameraZoom : public Function {
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
