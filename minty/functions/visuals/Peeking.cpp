#include "Peeking.h"

namespace cheat {
    static void onUpdate_6(app::GameManager* __this, app::MethodInfo* method);
    static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value);

    Peeking::Peeking() {
        f_Enabled = config::getValue("functions:Peeking", "enabled", false);
        f_Hotkey = Hotkey("functions:Peeking");

        HookManager::install(app::GameManager_Update, onUpdate_6);
        HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue);
    }

    Peeking& Peeking::getInstance() {
        static Peeking instance;
        return instance;
    }

    void Peeking::GUI() {
        ConfigCheckbox("Enable Peeking", f_Enabled, ";)");

        if (f_Enabled.getValue())
            f_Hotkey.Draw();
    }
    
    void Peeking::Outer() {
        if (f_Hotkey.IsPressed())
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
        auto& peeking = Peeking::getInstance();

        if (peeking.f_Enabled.getValue())
            value = 1;
        CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, __this, value);
    }

    app::GameObject* divingRoot;
    void onUpdate_6(app::GameManager* __this, app::MethodInfo* method) {
        auto& peeking = Peeking::getInstance();

        if (peeking.f_Enabled.getValue()) {
            if (divingRoot == nullptr || app::GameObject_get_active(divingRoot))
                divingRoot = app::GameObject_Find(string_to_il2cppi("/EffectPool/Eff_Player_Diving_Root"));
        } else {
            if (divingRoot) {
                app::GameObject_SetActive(divingRoot, false);

                divingRoot = nullptr;
            }
        }
        CALL_ORIGIN(onUpdate_6, __this, method);
    }
}
