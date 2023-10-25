#include "Peeking.h"

namespace cheat {
    static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value);

    Peeking::Peeking() {
        f_Enabled = config::getValue("functions:Peeking", "enabled", false);

        HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue);
    }

    Peeking& Peeking::getInstance() {
        static Peeking instance;
        return instance;
    }

    void Peeking::GUI() {
        ConfigCheckbox("Enable Peeking", f_Enabled, ";)");

        if (f_Enabled.getValue())
            Peeking::peekingHotkey.Draw();
    }
    
    void Peeking::Outer() {
        if (peekingHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void Peeking::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Enable Peeking");
    }

    std::string Peeking::getModule() {
        return _("Visuals");
    }

    void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value) {
        auto& Peeking = Peeking::getInstance();

        if (Peeking.f_Enabled.getValue())
            value = 1;
        CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, __this, value);
    }
}