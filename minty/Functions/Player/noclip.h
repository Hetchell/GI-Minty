#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
    class NoClip : public Function {
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
