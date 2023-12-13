#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
    class NoClip : public Function {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<bool> f_EnabledAltSpeed;
        ConfigField<bool> f_NoAnimation;
        ConfigField<bool> f_DetectCollisions;
        ConfigField<float> f_Speed;
        ConfigField<float> f_AltSpeed;

        Hotkey f_Hotkey;
        Hotkey f_HotkeyAlt;

        inline static float f_finalSpeed;

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string getModule() override;

        app::Vector3 prevPos, newPos, posCheck;

        static NoClip& getInstance();

        NoClip();
    };
}
