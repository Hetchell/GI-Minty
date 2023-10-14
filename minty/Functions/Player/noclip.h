#pragma once

#include "../il2cpp-appdata.h"
#include "../il2cppUtils.h"
#include "../Function.h"
#include "../../Hotkeys/Hotkey.h"
#include "../HookManager.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
    class NoClip : public FN {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<bool> f_EnabledAltSpeed;
        ConfigField<float> f_Speed;
        ConfigField<float> f_AltSpeed;

        inline static float f_finalSpeed;

        inline static Hotkey noClipHotkey = Hotkey("Noclip");
        inline static Hotkey noClipAltHotkey = Hotkey("AltNoclipSpeed");

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string getModule() override;

        static NoClip& getInstance();

        NoClip();
    };
}
