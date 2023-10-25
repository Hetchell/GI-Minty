#include "HideReaction.h"

namespace cheat {
    void MonoParticleDamageTextContainer_ShowReactionText(void* __this, void* ODIALFBPKOO, void* DDKPJLOMEIN, void* BHBLALOIKBM, void* AKFGHNDBADA, int MKOAJMOFAHC);

    HideReaction::HideReaction() : Function() {
        f_Enabled = config::getValue("functions:HideReaction", "enabled", false);

        HookManager::install(app::MonoParticleDamageTextContainer_ShowReactionText, MonoParticleDamageTextContainer_ShowReactionText);
    }

    HideReaction& HideReaction::getInstance() {
        static HideReaction instance;
        return instance;
    }

    void HideReaction::GUI() {
        ConfigCheckbox("Hide Reaction", f_Enabled, "Hide elemental reactions.");

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void HideReaction::Outer() {
        if (hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void HideReaction::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Hide Reaction");
    }

    std::string HideReaction::getModule() {
        return _("Visuals");
    }

    void MonoParticleDamageTextContainer_ShowReactionText(void* __this, void* ODIALFBPKOO, void* DDKPJLOMEIN, void* BHBLALOIKBM, void* AKFGHNDBADA, int MKOAJMOFAHC) {
        auto& hideReaction = HideReaction::getInstance();

        if (hideReaction.f_Enabled.getValue())
            return;
        CALL_ORIGIN(MonoParticleDamageTextContainer_ShowReactionText, __this, ODIALFBPKOO, DDKPJLOMEIN, BHBLALOIKBM, AKFGHNDBADA, MKOAJMOFAHC);
    }
}
