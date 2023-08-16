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

static float fovval = 45;
static bool iffov;
void InLevelCameraSetFov_Hook(app::Camera* __this, float value)
{
    if (!iffov)
        return;

    value = iffov ? fovval : 45;
    CALL_ORIGIN(InLevelCameraSetFov_Hook, __this, value);
}

static bool ifinitskipanim;
static bool ifskipanim;
static bool ifshowlevelup = true;
static uint32_t substatRollLevels[] = { 5, 9, 13, 17, 21 }; // artifact levels from the field go from 1 to 21, so we do +1
bool ShouldShowLevelUpDialog(app::MoleMole_EquipLevelUpDialogContext* dialog)
{
    if (ifshowlevelup)
    {
        /*
        util::log(M_Info, "DEBUG:");
        util::log(M_Info, "_prevLevel: %d", dialog->fields._prevLevel);
        util::log(M_Info, "_currLevel: %d", dialog->fields._currLevel);
        util::log(M_Info, "_powerUpRate: %d", dialog->fields._powerUpRate);
        */
        if (dialog->fields._equipType == app::MoleMole_Config_ItemType__Enum::ITEM_RELIQUARY)
        {
            const uint32_t prevLvl = dialog->fields._prevLevel;
            const uint32_t currLvl = dialog->fields._currLevel;
            return std::any_of(std::begin(substatRollLevels), std::end(substatRollLevels),
                [prevLvl, currLvl](uint32_t level) { return prevLvl < level && level <= currLvl; });
        }
    }
    return false;
}
void MoleMole_EquipLevelUpDialogContext_SetupView_Hook(app::MoleMole_EquipLevelUpDialogContext* __this)
{
    CALL_ORIGIN(MoleMole_EquipLevelUpDialogContext_SetupView_Hook, __this);

    if (ifskipanim && !ShouldShowLevelUpDialog(__this))
        app::MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog(__this);
}
void MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook(/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback)
{
    if (ifskipanim)
        return app::Action_Invoke(callback);

    CALL_ORIGIN(MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook, __this, startPer, endPer, callback);
}

void MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook(/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction)
{
    if (ifskipanim)
        return app::Action_Invoke(refreshViewAction);

    CALL_ORIGIN(MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook, __this, refreshViewAction);
}

static bool ifoti;
static bool ifinitoti;
void* InLevelPlayerProfilePageContext;

static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this)
{
    if (ifoti && !InLevelPlayerProfilePageContext)
    {
        __this->fields._levelMainPageContext->fields._countDownTime = __this->fields._levelMainPageContext->fields.EnterCountDown + 1.f;
    }
    return CALL_ORIGIN(MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook, __this);
}

static void MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook(void* __this)
{
    InLevelPlayerProfilePageContext = __this;
    CALL_ORIGIN(MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook, __this);
}

static void MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook(void* __this)
{
    CALL_ORIGIN(MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook, __this);
    InLevelPlayerProfilePageContext = nullptr;
}

namespace il2fns {
    void OpenTeamImm() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinitoti) {
            HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook);
            HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_ClearView, MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook);
            HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_SetupView, MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook);
            ifinitoti = true;
        }

        if (ImGui::Checkbox("OTI", &ifoti)) {
            //saveFuncStateToJson("NoCD", ifzoom);
        }
        ImGui::SameLine();
        HelpMarker("OTI.");

        /*
        if (value) {
            if (ifoti) {
                HookManager::detach(MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOff);
                ifoti = false;
            }
            HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, 
            MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOn);
        }
        else {
            HookManager::detach(LevelSceneElementViewPlugin_Tick_Hook);
            HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, 
            MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_HookOff);
            ifoti = true;
        }
        */
    }

    void SkipAnim() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinitskipanim) {
            HookManager::install(app::MoleMole_EquipLevelUpDialogContext_SetupView, MoleMole_EquipLevelUpDialogContext_SetupView_Hook);
            HookManager::install(app::MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook);
            HookManager::install(app::MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook);
            ifinitskipanim = true;
        }

        //ifzoom = readBoolFuncStateFromJson("NoCD");

        if (ImGui::Checkbox("Skip Enhance Animation", &ifskipanim)) {
            //saveFuncStateToJson("NoCD", ifzoom);
        }
        ImGui::SameLine();
        HelpMarker("Skip weapon and artifact enhancement animation.");
        
        if (ifskipanim) {
            if (ImGui::Checkbox("Show Level-Up Dialog For Substat Rolls", &ifshowlevelup)) {
                //saveFuncStateToJson("NoCD", ifzoom);
            }
            ImGui::SameLine();
            HelpMarker("Show level up dialog when artifacts roll substats\n"
                "(when hitting levels 4, 8, 12, 16, and 20).");
        }
    }

	void Change_UID(const char* uidText) {
        app::GameObject* uidTextObj = app::UnityEngine__GameObject__Find((app::String*)il2cpp_string_new("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        app::Component_1* uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, il2cpp_string_new("Text"));

		app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), il2cpp_string_new(uidText));
	}

    void ChestIndicator() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifchestinit) {
            HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck);
            ifchestinit = true;
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
            HookManager::install(app::MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, SCameraModuleInitialize_SetWarningLocateRatio_Hook);
            ifzoominit = true;
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
            //HookManager::install(app::Camera_set_fieldOfView, InLevelCameraSetFov_Hook);
            ifinitfov = true;
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