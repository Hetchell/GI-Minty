#include "dialogskip.h"

static bool ifdia;
static void CriwareMediaPlayer_UpdateOn(app::CriwareMediaPlayer* __this)
{
    app::CriwareMediaPlayer_Skip(__this);
    return CALL_ORIGIN(CriwareMediaPlayer_UpdateOn, __this);
}

void OnCutScenePageUpdate(app::InLevelCutScenePageContext* context, float value)
{
    auto talkDialog = context->fields._talkDialog;
    if (talkDialog == nullptr)
        return;

    app::UnityEngine__set__Timescale(value);

    //if (!talkDialog->fields._inSelect)
        //app::MoleMole_InLevelCutScenePageContext_OnFreeClick(context);
}

static void InLevelCutScenePageContext_UpdateView_HookOn(app::InLevelCutScenePageContext* __this)
{
    CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_HookOn, __this);
    OnCutScenePageUpdate(__this, 5);
}

static void InLevelCutScenePageContext_UpdateView_HookOff(app::InLevelCutScenePageContext* __this)
{
    CALL_ORIGIN(InLevelCutScenePageContext_UpdateView_HookOff, __this);
    OnCutScenePageUpdate(__this, 1);
}

static void InLevelCutScenePageContext_ClearView_Hook(app::InLevelCutScenePageContext* __this)
{
    app::UnityEngine__set__Timescale(1.f);
    CALL_ORIGIN(InLevelCutScenePageContext_ClearView_Hook, __this);
}

namespace il2fns {
    void DialogSkip(bool val) {
        if (val) {
            if (ifdia) {
                HookManager::detach(InLevelCutScenePageContext_UpdateView_HookOff);
                HookManager::detach(InLevelCutScenePageContext_ClearView_Hook);
                ifdia = false;
            }
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_HookOn);
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_ClearView, InLevelCutScenePageContext_ClearView_Hook);
        }
        else {
            HookManager::detach(InLevelCutScenePageContext_UpdateView_HookOn);
            HookManager::detach(InLevelCutScenePageContext_ClearView_Hook);
            HookManager::install(app::MoleMole_InLevelCutScenePageContext_UpdateView, InLevelCutScenePageContext_UpdateView_HookOff);
            ifdia = true;
        }
    }

    void CutsceneSkip(bool val) {
        if (val) {
            HookManager::install(app::CriwareMediaPlayer_Update, CriwareMediaPlayer_UpdateOn);
        }
        else {
            HookManager::detach(CriwareMediaPlayer_UpdateOn);
        }
    }
}