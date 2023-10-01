#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"
#include "../../Hotkeys/KeyBind.h"
#include "../Function.h"

namespace cheat {
    class Noclip : public FN {
    public:
        inline static bool ifNoclip;
        inline static bool ifAltSpeed;

        inline static float f_NoclipSpeed;
        inline static float f_NoclipAltSpeed;
        inline static float f_finalSpeed;

        inline static Hotkey noClipHotkey = Hotkey("Noclip");
        inline static Hotkey noClipAltHotkey = Hotkey("AltNoclipSpeed");

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string groupName = "Player";

        Noclip();

        std::string GetGroupName() override {
            return groupName;
        }
    };
}
