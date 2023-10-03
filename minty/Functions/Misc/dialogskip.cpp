#include "dialogskip.h"

namespace cheat {
    void OnCutScenePageUpdate(app::InLevelCutScenePageContext* context, float value)
    {
        if (!DialogSkip::ifDialogSkip)
            return;

        app::UnityEngine__set__Timescale(value);
        app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);

        /*
        auto talkDialog = context->fields._talkDialog;

        if (talkDialog == nullptr) {
            util::log(M_Info, "talkDialog == null");
            return;
        }

        util::log(M_Info, "_inSelect3: %d", talkDialog->fields.NHPGOHOAFKC);

        util::log(M_Info, "_inSelect5: %d", talkDialog->fields.MDICEHFCDFM);
        util::log(M_Info, "_inSelect11: %d", talkDialog->fields.FNOGAGEDMPP);
        if (talkDialog->fields.MDICEHFCDFM/* && f_AutoSelectDialog->enabled() && !isImportantAAA)
        {
            int32_t value = 0;
            auto object = il2cpp_value_box((app::Il2CppClass*)*app::Int32__TypeInfo, &value);
            app::Notify notify{};
            notify.type = app::MoleMole_NotifyTypes__Enum::DialogSelectNotify;
            notify.body = (app::Object*)object;
            app::MoleMole_TalkDialogContext_OnDialogSelectItem(talkDialog, &notify);
        }
        else if (!talkDialog->fields.MDICEHFCDFM)
            app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);
        */
    }

    static void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this)
    {
        CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_Hook, __this);
        OnCutScenePageUpdate(__this, DialogSkip::ifDialogSkip ? DialogSkip::fDialogSpeed : 1.0f);
    }

    static void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this)
    {
        app::UnityEngine__set__Timescale(1.f);
        CALL_ORIGIN(InLevelCutScenePageContext_ClearView_Hook, __this);
    }

    DialogSkip::DialogSkip() {
        ifDialogSkip = config::getValue("functions", "AutoTalk", false);
        HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_Hook);
        HookManager::install(app::MoleMole_InLevelCutScenePageContext_ClearView, InLevelCutScenePageContext_ClearView_Hook);
    }

    void DialogSkip::GUI() {
        CheckBoxFN("Auto-talk", ifDialogSkip, "AutoTalk")
        //ImGui::SameLine(); HelpMarker(_("Automatically goes through dialogue."));
        if (ifDialogSkip) {
            ImGui::Indent();
            ImGui::SliderFloat(_("Dialog speed"), &fDialogSpeed, 1.0, 50.0);
            dialogSkipHotkey.Draw();
            ImGui::Unindent();
        }
    }
    void DialogSkip::Status() {
        if (ifDialogSkip) {
            ImGui::Text(_("Dialog skip"));
        }
    }

    void DialogSkip::Outer() {
        if (dialogSkipHotkey.IsPressed())
            ifDialogSkip = !ifDialogSkip;
    }
}