#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class CameraZoom : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_CameraZoom;

		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static CameraZoom& getInstance();

		CameraZoom();
	};
}
