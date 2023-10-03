#include "cutsceneskip.h"

namespace cheat {
    static void CriwareMediaPlayer_Update(app::CriwareMediaPlayer* __this)
    {
        if (CutsceneSkip::ifSkipCutscene)
            app::CriwareMediaPlayer_Skip(__this);
        return CALL_ORIGIN(CriwareMediaPlayer_Update, __this);
    }

    CutsceneSkip::CutsceneSkip() {
        ifSkipCutscene = config::getValue("functions", "CutsceneSkip", false);
        HookManager::install(app::CriwareMediaPlayer_Update, CriwareMediaPlayer_Update);
    }

    void CutsceneSkip::GUI() {
        CheckBoxFN("Skip cutscenes", ifSkipCutscene, "CutsceneSkip")
        if (ifSkipCutscene) {
            skipCutsceneHotkey.Draw();
        }
        //HelpMarker(_("Skips cutscene. May break some game mechanics."));
    }

    void CutsceneSkip::Status() {
        if (ifSkipCutscene) {
            ImGui::Text(_("Cutscene skip"));
        }
    }

    void CutsceneSkip::Outer() {
        if (skipCutsceneHotkey.IsPressed())
            ifSkipCutscene = !ifSkipCutscene;
    }
}