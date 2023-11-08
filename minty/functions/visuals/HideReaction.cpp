#include "HideReaction.h"

namespace cheat {
    void MonoParticleDamageTextContainer_ShowReactionText(void* __this, void* reaction, void* elemType1, void* elemType2, void* attackee, int hitIndex);

    HideReaction::HideReaction() : Function() {
        f_Enabled = config::getValue("functions:HideReaction", "enabled", false);
        f_Hotkey = Hotkey("functions:HideReaction");

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
            f_Hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void HideReaction::Outer() {
        if (f_Hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void HideReaction::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Hide Reaction");
    }

    std::string HideReaction::getModule() {
        return _("Visuals");
    }

    void MonoParticleDamageTextContainer_ShowReactionText(void* __this, void* reaction, void* elemType1, void* elemType2, void* attackee, int hitIndex) {
        auto& hideReaction = HideReaction::getInstance();

        if (hideReaction.f_Enabled.getValue())
            return;
        CALL_ORIGIN(MonoParticleDamageTextContainer_ShowReactionText, __this, reaction, elemType1, elemType2, attackee, hitIndex);
    }
}
