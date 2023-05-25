#include "dialogskip.h"

static bool ifdia;
static bool ifcsc;
static bool ifdiainit;
static bool ifcscinit;
static void CriwareMediaPlayer_Update(app::CriwareMediaPlayer* __this)
{
    if (ifcsc)
        try {
        app::CriwareMediaPlayer_Skip(__this);
    }
    catch (...) {}
    return CALL_ORIGIN(CriwareMediaPlayer_Update, __this);
}

void OnCutScenePageUpdate(app::InLevelCutScenePageContext* context, float value)
{
    auto talkDialog = context->fields._talkDialog;
    if (talkDialog == nullptr)
        return;

    app::UnityEngine__set__Timescale(value);

    if (talkDialog->fields._inSelect /*&& f_AutoSelectDialog && !isImportant*/)
    {
        int32_t value = 0;
        //auto object = il2cpp_value_box((Il2CppClass*)*app::Int32__TypeInfo, &value);
        app::Notify notify{};
        notify.type = app::MoleMole_NotifyTypes__Enum::DialogSelectNotify;
        notify.body = (app::Object*)nullptr; // replace nullptr -> object
        app::MoleMole_TalkDialogContext_OnDialogSelectItem(talkDialog, &notify);
    }
    else if (!talkDialog->fields._inSelect)
        app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);
}

static void InLevelCutScenePageContext_UpdateView_Hook(app::InLevelCutScenePageContext* __this)
{
    CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_Hook, __this);
    try {
        OnCutScenePageUpdate(__this, ifdia ? 5.0f : 1.0f);
    }
    catch (...) {}
}

static void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this)
{
    try {
        app::UnityEngine__set__Timescale(1.f);
    }
    catch (...) {}
    CALL_ORIGIN(InLevelCutScenePageContext_ClearView_Hook, __this);
}

namespace il2fns {
    void DialogSkip(bool value) {
        if (!ifdiainit) {
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_Hook);
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_ClearView, InLevelCutScenePageContext_ClearView_Hook); ifdiainit = true; }
        ifdia = value;
    }

    void CutsceneSkip(bool value) {
        if (!ifcscinit)
            HookManager::install(app::CriwareMediaPlayer_Update, CriwareMediaPlayer_Update); ifcscinit = true;
        ifcsc = value;
    }
}