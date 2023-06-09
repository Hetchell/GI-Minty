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
static bool ifzoominit;
static bool ifzoom;
void SCameraModuleInitialize_SetWarningLocateRatio_Hook(app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data)
{
    data->currentWarningLocateRatio = static_cast<double>(ifzoom ? zoomval : 1);
    CALL_ORIGIN(SCameraModuleInitialize_SetWarningLocateRatio_Hook, __this, deltaTime, data);
}

static float fovval;
static bool iffov;
void InLevelCameraSetFov_Hook(app::Camera* __this, float value)
{
    value = iffov ? fovval : 45;
    CALL_ORIGIN(InLevelCameraSetFov_Hook, __this, value);
}

namespace il2fns {
	void Change_UID(const char* uidText) {
        app::GameObject* uidTextObj = app::UnityEngine__GameObject__Find((app::String*)il2cpp_string_new("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        app::Component_1* uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, il2cpp_string_new("Text"));

		app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), il2cpp_string_new(uidText));
	}

    void ChestIndicator() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifchestinit) {
            HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck); ifchestinit = true;
        }

        ifChest = readBoolFuncStateFromJson("ShowChest");

        if (ImGui::Checkbox("Show chests indicators", &ifChest)) {
            saveFuncStateToJson("ShowChest", ifChest);
        }
        ImGui::SameLine();
        HelpMarker("Shows indicators for all chests and TP points.");
    }

    void CameraZoom() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifzoominit) {
            HookManager::install(app::MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, SCameraModuleInitialize_SetWarningLocateRatio_Hook); ifzoominit = true;
        }

        //ifzoom = readBoolFuncStateFromJson("NoCD");

        if (ImGui::Checkbox("Camera zoom", &ifzoom)) {
            //saveFuncStateToJson("NoCD", ifzoom);
        }
        ImGui::SameLine();
        HelpMarker("Changes distance from camera.");
        if (ifzoom) {
            ImGui::SliderFloat("Target Zoom", &zoomval, 0, 500);
        }
    }

    void SetFov() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinitfov) {
            HookManager::install(app::Camera_set_fieldOfView, InLevelCameraSetFov_Hook); ifinitfov = true;
        }

        //ifzoom = readBoolFuncStateFromJson("NoCD");

        if (ImGui::Checkbox("Change field of view", &iffov)) {
            //saveFuncStateToJson("NoCD", ifzoom);
        }
        ImGui::SameLine();
        HelpMarker("Changes camera's field of view.");
        if (iffov) {
            ImGui::SliderFloat("Target FOV", &fovval, 10, 180);
        }
    }
}