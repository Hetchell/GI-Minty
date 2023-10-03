#include "bootyfixer.h"

namespace cheat {
    static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value)
    {
        if (Peeking::ifPeeking)
            value = 1;
        CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, __this, value);
    }

    Peeking::Peeking() {
        ifPeeking = config::getValue("functions", "Peeking", false);
        HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue);
    }

    void Peeking::GUI() {
        CheckBoxFN("Enable peeking", ifPeeking, "Peeking");
        if (ifPeeking) {
            Peeking::peekingHotkey.Draw();
        }
    }
    
    void Peeking::Outer() {
        if (peekingHotkey.IsPressed())
            ifPeeking = !ifPeeking; config::setValue("functions", "Peeking", ifPeeking);
    }

    void Peeking::Status() {
        if (ifPeeking) {
            ImGui::Text("Peeking");
        }
    }
}