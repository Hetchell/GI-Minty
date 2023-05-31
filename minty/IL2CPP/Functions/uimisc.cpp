#include "uimisc.h"

static bool ifElem;
static void LevelSceneElementViewPlugin_Tick_Hook(app::LevelSceneElementViewPlugin* __this, float inDeltaTime) {
     __this->fields._triggerElementView = ifElem;
    CALL_ORIGIN(LevelSceneElementViewPlugin_Tick_Hook, __this, inDeltaTime);
}

static bool ifChest;
static bool ifchestinit;
static bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
    if (ifChest) {
        if (__this->fields._dataItem != nullptr)
        {
            try {
                app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
            }
            catch (...) {}
        }
    } else app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
    return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
}

//static bool IndicatorPlugin_DoCheckOff(app::LCIndicatorPlugin* __this) {
//    app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
//    return CALL_ORIGIN(IndicatorPlugin_DoCheckOff, __this);
//>>>>>>> 2569c84d9210cec7c323394b6e05944c1df4a59a
//}

static bool ifoti;
static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOn(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this)
{
    __this->fields._levelMainPageContext->fields._countDownTime = 0;
    return CALL_ORIGIN(MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOn, __this);
}

static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOff(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this)
{
    __this->fields._levelMainPageContext->fields._countDownTime = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
    return CALL_ORIGIN(MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOff, __this);
}

static float zoomval;
void SCameraModuleInitialize_SetWarningLocateRatio_Hook(app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data)
{
    try {
        data->currentWarningLocateRatio = static_cast<double>(zoomval);
    }
    catch (...) {}
    CALL_ORIGIN(SCameraModuleInitialize_SetWarningLocateRatio_Hook, __this, deltaTime, data);
}

namespace il2fns {
	void Change_UID(const char* uidText) {
        app::GameObject* uidTextObj = app::UnityEngine__GameObject__Find((app::String*)il2cpp_string_new("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        app::Component_1* uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, il2cpp_string_new("Text"));

		app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), il2cpp_string_new(uidText));
	}

    void ChestIndicator(bool value) {
        if (!ifchestinit)
            HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck); ifchestinit = true;
        ifChest = value;
    }

    void ElemSight(bool value) {
        static bool ifinit = false;
        if (!ifinit)
            HookManager::install(app::MoleMole_LevelSceneElementViewPlugin_Tick, LevelSceneElementViewPlugin_Tick_Hook); ifinit = true;
        ifElem = value;
    }

    void OpenTeamImm(bool value) {
        if (value) {
            if (ifoti) {
                HookManager::detach(MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOff);
                ifoti = false;
            }
            HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOn);
        }
        else {
            HookManager::detach(LevelSceneElementViewPlugin_Tick_Hook);
            HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOff);
            ifoti = true;
        }
    }

    void CameraZoom(float value) {
        static bool ifinit;
        if (!ifinit)
            HookManager::install(app::MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, SCameraModuleInitialize_SetWarningLocateRatio_Hook); ifinit = true;
        zoomval = value;
    }

    void TurnFog(bool value) {
        app::RenderSettings_set_fog(!value);
    }
}