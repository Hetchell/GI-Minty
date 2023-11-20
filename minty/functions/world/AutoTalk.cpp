#include "AutoTalk.h"

namespace cheat {
    void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this);
    void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this);

    AutoTalk::AutoTalk() {
        f_Enabled = config::getValue("functions:AutoTalk", "enabled", false);
        f_TalkSpeed = config::getValue("functions:AutoTalk", "talkSpeed", 1.0f);
        f_Hotkey = Hotkey("functions:AutoTalk");

        HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_Hook);
        HookManager::install(app::MoleMole_InLevelCutScenePageContext_ClearView, InLevelCutScenePageContext_ClearView_Hook);
    }

    AutoTalk& AutoTalk::getInstance() {
        static AutoTalk instance;
        return instance;
    }

    void AutoTalk::GUI() {
        ConfigCheckbox("Auto Talk", f_Enabled, _("Automatically goes through dialogue."));

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            ConfigSliderFloat(_("Dialog speed"), f_TalkSpeed, 1.0f, 50.0f);
            f_Hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void AutoTalk::Status() {
        if (f_Enabled.getValue())
            ImGui::Text(_("AutoTalk"));
    }

    void AutoTalk::Outer() {
        if (f_Hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    std::string AutoTalk::getModule() {
        return _("World");
    }

    void AutoTalk::OnCutScenePageUpdate(app::InLevelCutScenePageContext* context) {
        auto& autoTalk = AutoTalk::getInstance();
        bool enabled = autoTalk.f_Enabled.getValue();

        if (!enabled)
            return;

        app::Time_set_timeScale(enabled ? autoTalk.f_TalkSpeed.getValue() : 1.0f);
        app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);
    }

    void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this) {
        CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_Hook, __this);
        AutoTalk::getInstance().OnCutScenePageUpdate(__this);
    }

    void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this) {
        app::Time_set_timeScale(1.0f);
        CALL_ORIGIN(InLevelCutScenePageContext_ClearView_Hook, __this);
    }
}
