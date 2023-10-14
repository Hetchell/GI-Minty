#include "uimisc.h"

namespace cheat {
    static bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this);
    void SCameraModuleInitialize_SetWarningLocateRatio_Hook(app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data);
    void InLevelCameraSetFov_Hook(app::Camera* __this, float value)
    {
        //printf("boba");
        if (!UIMisc::ifFovChanger)
            return;

        value = UIMisc::ifFovChanger ? UIMisc::i_Fov : 45.0f;
        CALL_ORIGIN(InLevelCameraSetFov_Hook, __this, value);
    }
    bool ShouldShowLevelUpDialog(app::MoleMole_EquipLevelUpDialogContext* dialog);
    void MoleMole_EquipLevelUpDialogContext_SetupView_Hook(app::MoleMole_EquipLevelUpDialogContext* __this);
    void MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook(void* __this, float startPer, float endPer, void* callback);
    void MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook(void* __this, void* refreshViewAction);
    static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this);
    static void MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook(void* __this);
    static void MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook(void* __this);
    void Change_UID(const char* uidText);

    UIMisc::UIMisc() {
        // OTI hooks
        HookManager::install(app::MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook);
        HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_ClearView, MoleMole_InLevelPlayerProfilePageContext_ClearView_Hook);
        HookManager::install(app::MoleMole_InLevelPlayerProfilePageContext_SetupView, MoleMole_InLevelPlayerProfilePageContext_SetupView_Hook);
        // Skip enhance anim hooks
        HookManager::install(app::MoleMole_EquipLevelUpDialogContext_SetupView, MoleMole_EquipLevelUpDialogContext_SetupView_Hook);
        HookManager::install(app::MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook);
        HookManager::install(app::MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook);
        // Camera zoom hooks
        HookManager::install(app::MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, SCameraModuleInitialize_SetWarningLocateRatio_Hook);
        // FOV hooks
        HookManager::install(app::Camera_set_fieldOfView, InLevelCameraSetFov_Hook);
        // Chest indic
        HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck);

        f_CameraZoom = 10;
        i_Fov = 45;

        showLevelUp = true;

        ifOTI = config::getValue("functions", "OTI", false);
        ifChestIndic = config::getValue("functions", "ShowChest", false);
        ifSkipAnim = config::getValue("functions", "SkipAnim", false);
        ifCameraZoom = config::getValue("functions", "CameraZoom", false);
        ifFovChanger = config::getValue("functions", "FOVChanger", false);
        ifUid = config::getValue("functions", "CustomUID", false);
    }

    void UIMisc::GUI() {
        CheckBoxFN("Open team immediately", ifOTI, "OTI")
        if (ifOTI) {
            ImGui::Indent();
            otiHotkey.Draw();
            ImGui::Unindent();
        }

        CheckBoxFN("Show chest indicators", ifChestIndic, "ShowChest")
        if (ifChestIndic) {
            ImGui::Indent();
            chestIndicHotkey.Draw();
            ImGui::Unindent();
        }

        CheckBoxFN("Skip enhance animations", ifSkipAnim, "SkipAnim")
        if (ifSkipAnim) {
            ImGui::Indent();
            ImGui::Checkbox("Show level up screens", &showLevelUp);
            skipAnimHotkey.Draw();
            ImGui::Unindent();
        }

        CheckBoxFN("Camera zoom", ifCameraZoom, "CameraZoom")
        if (ifCameraZoom) {
            ImGui::Indent();
            ImGui::SliderFloat("Zoom value", &f_CameraZoom, 10, 500);
            cameraZoomHotkey.Draw();
            ImGui::Unindent();
        }

        CheckBoxFN("FOV changer", ifFovChanger, "FOVChanger")
        if (ifFovChanger) {
            ImGui::Indent();
            ImGui::SliderInt("FOV value", &i_Fov, 10, 170);
            fovChangerHotkey.Draw();
            ImGui::Unindent();
        }

        /*CheckBoxFN("Custom UID", ifUid, "CustomUID")
        if (ifUid) {
            ImGui::Indent();
            if (ImGui::InputText("Custom UID", Uid_buf, sizeof(Uid_buf))) {
                Change_UID(Uid_buf);
            }
            uidHotkey.Draw();
            ImGui::Unindent();
        }*/
    }

    void UIMisc::Outer() {
        if (chestIndicHotkey.IsPressed())
            ifChestIndic = !ifChestIndic;
        if (cameraZoomHotkey.IsPressed())
            ifCameraZoom = !ifCameraZoom;
        if (fovChangerHotkey.IsPressed())
            ifFovChanger = !ifFovChanger;
        if (skipAnimHotkey.IsPressed())
            ifSkipAnim = !ifSkipAnim;
        if (otiHotkey.IsPressed())
            ifOTI = !ifOTI;
        if (uidHotkey.IsPressed())
            ifUid = !ifUid;
    }

    void UIMisc::Status() {
        if (ifOTI) {
            ImGui::Text("OTI");
        }
        if (ifFovChanger) {
            ImGui::Text("FOV (%i)", i_Fov);
        }
        if (ifSkipAnim) {
            ImGui::Text(showLevelUp ? "SkipAnim|ShowLevelUp" : "SkipAnim");
        }
        if (ifCameraZoom) {
            ImGui::Text("Camera zoom (%.1f)", f_CameraZoom);
        }
        if (ifChestIndic) {
            ImGui::Text("Show Chest Indicators");
        }
        if (ifUid) {
            ImGui::Text("Show Chest Indicators");
        }
    }

    static bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
        if (UIMisc::ifChestIndic) {
            if (__this->fields._dataItem != nullptr)
            {
                app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
            }
        }
        else app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
        return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
    }

    void SCameraModuleInitialize_SetWarningLocateRatio_Hook(app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data)
    {
        data->currentWarningLocateRatio = static_cast<double>(UIMisc::ifCameraZoom ? UIMisc::f_CameraZoom : 1.f);
        CALL_ORIGIN(SCameraModuleInitialize_SetWarningLocateRatio_Hook, __this, deltaTime, data);
    }

    static uint32_t substatRollLevels[] = { 5, 9, 13, 17, 21 }; // artifact levels from the field go from 1 to 21, so we do +1
    bool ShouldShowLevelUpDialog(app::MoleMole_EquipLevelUpDialogContext* dialog)
    {
        if (UIMisc::showLevelUp)
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

        if (UIMisc::ifSkipAnim && !ShouldShowLevelUpDialog(__this))
            app::MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog(__this);
    }

    void MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook(/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback)
    {
        if (UIMisc::ifSkipAnim)
            return app::Action_Invoke(callback);

        CALL_ORIGIN(MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook, __this, startPer, endPer, callback);
    }

    void MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook(/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction)
    {
        if (UIMisc::ifSkipAnim)
            return app::Action_Invoke(refreshViewAction);

        CALL_ORIGIN(MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook, __this, refreshViewAction);
    }

    void* InLevelPlayerProfilePageContext;
    static bool MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext_Hook(app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this)
    {
        if (UIMisc::ifOTI && !InLevelPlayerProfilePageContext)
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

    /*app::GameObject* uidTextObj;
    app::Component_1* uidTextComp;
	void Change_UID(const char* uidText) {
        while (!uidTextObj)
            uidTextObj = app::UnityEngine__GameObject__Find(string_to_il2cppi("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        while (!uidTextComp)
            uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, string_to_il2cppi("Text"));

		app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), string_to_il2cppi(uidText));
	}*/
}