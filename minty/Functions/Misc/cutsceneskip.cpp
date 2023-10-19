#include "CutsceneSkip.h"

namespace cheat {
    static void CriwareMediaPlayer_Update(app::CriwareMediaPlayer* __this, app::MethodInfo* method);

    CutsceneSkip::CutsceneSkip() {
        f_Enabled = config::getValue("functions:CutsceneSkip", "enabled", false);

        HookManager::install(app::CriwareMediaPlayer_Update, CriwareMediaPlayer_Update);
    }

    CutsceneSkip& CutsceneSkip::getInstance() {
        static CutsceneSkip instance;
        return instance;
    }

    void CutsceneSkip::GUI() {
        ConfigCheckbox("Skip Cutscene", f_Enabled);
        ImGui::SameLine();
        HelpMarker(_("Skips cutscene. May break some game mechanics."));

        if (f_Enabled.getValue())
            skipCutsceneHotkey.Draw();
    }

    void CutsceneSkip::Status() {
        if (f_Enabled.getValue())
            ImGui::Text(_("Skip Cutscene"));
    }

    void CutsceneSkip::Outer() {
        if (skipCutsceneHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    std::string CutsceneSkip::getModule() {
        return _("Misc");
    }

    void CriwareMediaPlayer_Update(app::CriwareMediaPlayer* __this, app::MethodInfo* method) {
        auto& CutsceneSkip = CutsceneSkip::getInstance();

        LOG_DEBUG("Skip Cutscene enabled: %d", CutsceneSkip.f_Enabled.getValue());
        if (CutsceneSkip.f_Enabled.getValue())
            app::CriwareMediaPlayer_Skip(__this, method);
        LOG_DEBUG("skipped!");
        return CALL_ORIGIN(CriwareMediaPlayer_Update, __this, method);
    }
}