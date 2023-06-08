#include "uimisc.h"

static bool ifinitfov;
static bool ifinitsight;

static bool ifChest;
static bool ifchestinit;
static bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
    if (ifChest) {
        if (__this->fields._dataItem != nullptr)
        {
            app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
        }
    } else app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
    return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
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

static float fovval;
void InLevelCameraSetFov_Hook(app::Camera* __this, float value)
{
    value = fovval;
    CALL_ORIGIN(InLevelCameraSetFov_Hook, __this, value);
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

    void CameraZoom(float value) {
        static bool ifinit;
        if (!ifinit)
            HookManager::install(app::MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, SCameraModuleInitialize_SetWarningLocateRatio_Hook); ifinit = true;
        zoomval = value;
    }

    void SetFov(float value) {
        if (!ifinitfov)
            HookManager::install(app::Camera_set_fieldOfView, InLevelCameraSetFov_Hook); ifinitfov = true;
        fovval = value;
    }
}