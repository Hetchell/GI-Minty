#include "HideDamage.h"

namespace cheat {
    void MonoParticleDamageTextContainer_ShowDamageText(void* __this, void* MPNOONEAJLB, void* AKFGHNDBADA);

    HideDamage::HideDamage() : Function() {
        f_Enabled = config::getValue("functions:HideDamage", "enabled", false);

        HookManager::install(app::MonoParticleDamageTextContainer_ShowDamageText, MonoParticleDamageTextContainer_ShowDamageText);
    }

    HideDamage& HideDamage::getInstance() {
        static HideDamage instance;
        return instance;
    }

    void HideDamage::GUI() {
        ConfigCheckbox("Hide Damage", f_Enabled, "Hide damage numbers.");

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void HideDamage::Outer() {
        if (hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void HideDamage::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Hide Damage");
    }

    std::string HideDamage::getModule() {
        return _("Misc");
    }

    void MonoParticleDamageTextContainer_ShowDamageText(void* __this, void* MPNOONEAJLB, void* AKFGHNDBADA) {
        auto& hideDamage = HideDamage::getInstance();

        if (hideDamage.f_Enabled.getValue())
            return;
        CALL_ORIGIN(MonoParticleDamageTextContainer_ShowDamageText, __this, MPNOONEAJLB, AKFGHNDBADA);
    }
}
