#include "CutsceneSkip.h"

namespace cheat {
    static void CriwareMediaPlayer_Update(app::CriwareMediaPlayer* __this);

    CutsceneSkip::CutsceneSkip() {
        f_Enabled = config::getValue("functions:CutsceneSkip", "enabled", false);

        HookManager::install(app::CriwareMediaPlayer_Update, CriwareMediaPlayer_Update);
    }

    CutsceneSkip& CutsceneSkip::getInstance() {
        static CutsceneSkip instance;
        return instance;
    }

    void CutsceneSkip::GUI() {
        ConfigCheckbox("Skip cutscenes", f_Enabled);
        ImGui::SameLine();
        HelpMarker(_("Skips cutscene. May break some game mechanics."));

        if (f_Enabled.getValue())
            skipCutsceneHotkey.Draw();
    }

    void CutsceneSkip::Status() {
        if (f_Enabled.getValue())
            ImGui::Text(_("Cutscene skip"));
    }

    void CutsceneSkip::Outer() {
        if (skipCutsceneHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    std::string CutsceneSkip::getModule() {
        return _("Misc");
    }

    static void CriwareMediaPlayer_Update(app::CriwareMediaPlayer* __this) {
        auto& CutsceneSkip = CutsceneSkip::getInstance();

        if (CutsceneSkip.f_Enabled.getValue())
            app::CriwareMediaPlayer_Skip(__this);
        return CALL_ORIGIN(CriwareMediaPlayer_Update, __this);
    }
}