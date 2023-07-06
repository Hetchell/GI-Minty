#include "dialogskip.h"

static bool ifdia;
static bool ifcsc;
static bool ifdiainit;
static bool ifcscinit;
static float diaSpeed;
static void CriwareMediaPlayer_Update(app::CriwareMediaPlayer* __this)
{
    if (ifcsc)
        app::CriwareMediaPlayer_Skip(__this);
    return CALL_ORIGIN(CriwareMediaPlayer_Update, __this);
}

void OnCutScenePageUpdate(app::InLevelCutScenePageContext* context, float value)
{
    if (!ifdia)
        return;

    auto talkDialog = context->fields._talkDialog12;
    if (talkDialog == nullptr) {
        util::log(M_Info, "talkDialog == null :cry:");
        return;
    }

    app::UnityEngine__set__Timescale(value);
    app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);

    //util::log(M_Info, "inselect: %d", talkDialog->fields._inSelect);
    //util::log(M_Info, "inselect2: %d", talkDialog->fields._inSelect2);
    //util::log(M_Info, "inselect3: %d", talkDialog->fields._inSelect3);
    //util::log(M_Info, "inselect4: %d", talkDialog->fields._inSelect4);
    //util::log(M_Info, "inselect5: %d", talkDialog->fields._inSelect5);
    //util::log(M_Info, "inselect6: %d", talkDialog->fields._inSelect6);
    //util::log(M_Info, "inselect7: %d", talkDialog->fields._inSelect7);
    //util::log(M_Info, "inselect8: %d", talkDialog->fields._inSelect8);
    //util::log(M_Info, "inselect9: %d", talkDialog->fields._inSelect9);
    //util::log(M_Info, "inselect10: %d", talkDialog->fields._inSelect10);
    //util::log(M_Info, "inselect11: %d", talkDialog->fields._inSelect11);
    //util::log(M_Info, "inselect12: %d", talkDialog->fields._inSelect12);
    //util::log(M_Info, "inselect13: %d", talkDialog->fields._inSelect13);
    //util::log(M_Info, "inselect14: %d", talkDialog->fields._inSelect14);
    //util::log(M_Info, "inselect15: %d", talkDialog->fields._inSelect15);
    //util::log(M_Info, "inselect16: %d", talkDialog->fields._inSelect16);
    //util::log(M_Info, "inselect17: %d", talkDialog->fields._inSelect17);
    /*if (talkDialog->fields._inSelect/* && f_AutoSelectDialog->enabled() && !isImportantAAA)
    {
        int32_t value = 0;
        auto object = il2cpp_value_box((app::Il2CppClass*)*app::Int32__TypeInfo, &value);
        app::Notify notify{};
        notify.type = app::MoleMole_NotifyTypes__Enum::DialogSelectNotify;
        notify.body = (app::Object*)object;
        app::MoleMole_TalkDialogContext_OnDialogSelectItem(talkDialog, &notify);
    }
    else if (!talkDialog->fields._inSelect)
        app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);*/
}

static void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this)
{
    CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_Hook, __this);
    OnCutScenePageUpdate(__this, ifdia ? diaSpeed : 1.0f);
}

static void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this)
{
    app::UnityEngine__set__Timescale(1.f);
    CALL_ORIGIN(InLevelCutScenePageContext_ClearView_Hook, __this);
}

namespace il2fns {
    void DialogSkip() {
        static bool ifDialog = readBoolFuncStateFromJson("AutoTalk");
        ifdia = ifDialog;

        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifdiainit) {
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_Hook);
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_ClearView, InLevelCutScenePageContext_ClearView_Hook); ifdiainit = true; 
        }

        if (ImGui::Checkbox("Auto-talk", &ifDialog)) {
            saveFuncStateToJson("AutoTalk", ifDialog);
            if (!ifDialog)
                diaSpeed = 1; ifdia = false;
        } ImGui::SameLine(); HelpMarker("Automatically goes through dialogue.");

        if (ifDialog) {
            ImGui::Indent();
            ImGui::SliderFloat("Dialog speed", &diaSpeed, 1.0, 50.0);
            ImGui::Unindent();
        }
    }

    void CutsceneSkip() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifcscinit) {
            HookManager::install(app::CriwareMediaPlayer_Update, CriwareMediaPlayer_Update); ifcscinit = true;
        }

        static bool ifcutscene = readBoolFuncStateFromJson("CutsceneSkip");
        ifcsc = ifcutscene;

        if (ImGui::Checkbox("Skip cutscene", &ifcutscene)) {
            saveFuncStateToJson("CutsceneSkip", ifcutscene);
            ifcsc = ifcutscene;
        }
        ImGui::SameLine();
        HelpMarker("Skips cutscene. May break some game mechanics.");
    }
}