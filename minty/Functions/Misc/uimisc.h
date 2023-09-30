#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../HookManager.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"

namespace cheat {
	class UIMisc : public FN {
	public:
		inline static bool ifChestIndic;
		inline static bool ifCameraZoom;
		inline static bool ifFovChanger;
		inline static bool ifSkipAnim;
		inline static bool ifOTI;
		inline static bool ifUid;

		inline static Hotkey chestIndicHotkey = Hotkey("ChestIndic");
		inline static Hotkey cameraZoomHotkey = Hotkey("CameraZoom");
		inline static Hotkey fovChangerHotkey = Hotkey("FovChanger");
		inline static Hotkey skipAnimHotkey = Hotkey("SkipAnim");
		inline static Hotkey otiHotkey = Hotkey("OTI");
		inline static Hotkey uidHotkey = Hotkey("Uid");


		inline static float f_CameraZoom;
		inline static int i_Fov;

		inline static bool showLevelUp;

		inline static std::string s_Uid;
		inline static char Uid_buf[256];

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName = _("Misc");

		UIMisc();
	};
}