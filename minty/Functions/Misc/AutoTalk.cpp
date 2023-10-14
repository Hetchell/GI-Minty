#include "AutoTalk.h"

namespace cheat {
    static void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this);
    static void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this);
    static void OnCutScenePageUpdate(app::InLevelCutScenePageContext* context, float value);

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

    void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this) {
        auto& AutoTalk = AutoTalk::getInstance();

        CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_Hook, __this);
        OnCutScenePageUpdate(__this, AutoTalk.f_Enabled.getValue() ? AutoTalk.f_TalkSpeed.getValue() : 1.0f);
    }

    void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this) {
        app::UnityEngine__set__Timescale(1.0f);
        CALL_ORIGIN(InLevelCutScenePageContext_ClearView_Hook, __this);
    }

    void OnCutScenePageUpdate(app::InLevelCutScenePageContext* context, float value) {
        auto& AutoTalk = AutoTalk::getInstance();

        if (!AutoTalk.f_Enabled.getValue())
            return;

        app::UnityEngine__set__Timescale(value);
        app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);
    }
}
