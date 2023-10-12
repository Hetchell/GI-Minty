#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"


namespace cheat {
	class AutoTP : public FN {
	public:
		struct TP {
			std::string name;
			std::string description;
			app::Vector3 position;
		};

		inline static bool ifAutoTP = false;
		inline static bool ifAutomatic = false;
		inline static bool ifManual = false;
		inline static float timerWait = 0.0f;
		inline static bool b_startTeleporting = false;
		inline static TP currentPoint = {};
		inline static char folderPathBuffer[1024] = "";
		static std::vector<TP> parseds;
		inline static int currentPointIndex = 0;

		inline static Hotkey teleportBackHotkey = Hotkey("TeleportBack");
		inline static Hotkey teleportForwardHotkey = Hotkey("TeleportForward");
		inline static Hotkey autoTeleportHotkey = Hotkey("ToggleAutomatic");


		std::string groupName = "World";

		std::string GetGroupName() override {
			return groupName;
		}

		AutoTP();

		void GUI();
		void Outer() override;
		void Status() override;
	};
}
