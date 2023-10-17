#include "AutoTalk.h"

namespace cheat {
    void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this);
    void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this);

    AutoTalk::AutoTalk() {
        f_Enabled = config::getValue("functions:AutoTalk", "enabled", false);
        f_TalkSpeed = config::getValue("functions:AutoTalk", "talkSpeed", 1.0f);

        HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_Hook);
        HookManager::install(app::MoleMole_InLevelCutScenePageContext_ClearView, InLevelCutScenePageContext_ClearView_Hook);
    }

    AutoTalk& AutoTalk::getInstance() {
        static AutoTalk instance;
        return instance;
    }

    void AutoTalk::GUI() {
        ConfigCheckbox("Auto Talk", f_Enabled);
        ImGui::SameLine();
        HelpMarker(_("Automatically goes through dialogue."));

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            ConfigSliderFloat(_("Dialog speed"), f_TalkSpeed, 1.0f, 50.0f);
            dialogSkipHotkey.Draw();
            ImGui::Unindent();
        }
    }
    void AutoTalk::Status() {
        if (f_Enabled.getValue())
            ImGui::Text(_("AutoTalk"));
    }

    void AutoTalk::Outer() {
        if (dialogSkipHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    std::string AutoTalk::getModule() {
        return _("Misc");
    }

    void AutoTalk::OnCutScenePageUpdate(app::InLevelCutScenePageContext* context) {
        auto& AutoTalk = AutoTalk::getInstance();
        bool enabled = AutoTalk.f_Enabled.getValue();

        if (!enabled)
            return;

        app::Time_set_timeScale(enabled ? AutoTalk.f_TalkSpeed.getValue() : 1.0f);
        app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);
    }

    void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this) {
        CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_Hook, __this);

        auto& AutoTalk = AutoTalk::getInstance();

        AutoTalk.OnCutScenePageUpdate(__this);
    }

    void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this) {
        app::Time_set_timeScale(1.0f);
        CALL_ORIGIN(InLevelCutScenePageContext_ClearView_Hook, __this);
    }
}
