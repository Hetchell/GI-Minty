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
    auto talkDialog = context->fields._talkDialog;
    if (talkDialog == nullptr)
        return;

    app::UnityEngine__set__Timescale(value);
    app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);
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
    void DialogSkip(bool value, float speed) {
        if (!ifdiainit) {
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_Hook);
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_ClearView, InLevelCutScenePageContext_ClearView_Hook); ifdiainit = true; }
        ifdia = value;
        diaSpeed = speed;
    }

    void CutsceneSkip(bool value) {
        if (!ifcscinit)
            HookManager::install(app::CriwareMediaPlayer_Update, CriwareMediaPlayer_Update); ifcscinit = true;
        ifcsc = value;
    }
}