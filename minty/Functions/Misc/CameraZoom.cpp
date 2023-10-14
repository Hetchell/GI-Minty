#include "CameraZoom.h"

namespace cheat {
    static void SCameraModuleInitialize_SetWarningLocateRatio_Hook(app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data);

    CameraZoom::CameraZoom() {
        f_Enabled = config::getValue("functions:CameraZoom", "enabled", false);
        f_CameraZoom = config::getValue("functions:CameraZoom", "cameraZoom", 10.0f);

        HookManager::install(app::MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, SCameraModuleInitialize_SetWarningLocateRatio_Hook);
    }

    CameraZoom& CameraZoom::getInstance() {
        static CameraZoom instance;
        return instance;
    }

    void CameraZoom::GUI() {
        ConfigCheckbox("Camera zoom", f_Enabled);

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            ConfigSliderFloat("Zoom value", f_CameraZoom, 10.0f, 500.0f);
            cameraZoomHotkey.Draw();
            ImGui::Unindent();
        }
    }

    void CameraZoom::Outer() {
        if (cameraZoomHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void CameraZoom::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Camera zoom (%.1f)", f_CameraZoom);
    }

    std::string CameraZoom::getModule() {
        return _("Misc");
    }

    void SCameraModuleInitialize_SetWarningLocateRatio_Hook(app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data) {
        auto& CameraZoom = CameraZoom::getInstance();

        data->currentWarningLocateRatio = static_cast<double>(CameraZoom.f_Enabled.getValue() ? CameraZoom.f_CameraZoom.getValue() : 1.0f);
        CALL_ORIGIN(SCameraModuleInitialize_SetWarningLocateRatio_Hook, __this, deltaTime, data);
    }
}
