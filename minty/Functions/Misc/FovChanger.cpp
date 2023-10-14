#include "FovChanger.h"

namespace cheat {
    static void InLevelCameraSetFov_Hook(app::Camera* __this, float value);

    FovChanger::FovChanger() {
        f_Enabled = config::getValue("functions:FovChanger", "enabled", false);
        f_Fov = config::getValue("functions:FovChanger", "fov", 45.0f);

        HookManager::install(app::Camera_set_fieldOfView, InLevelCameraSetFov_Hook);
    }

    FovChanger& FovChanger::getInstance() {
        static FovChanger instance;
        return instance;
    }

    void FovChanger::GUI() {
        ConfigCheckbox("FOV Changer", f_Enabled);

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            ConfigSliderFloat("FOV value", f_Fov, 10.0f, 170.0f);
            fovChangerHotkey.Draw();
            ImGui::Unindent();
        }
    }

    void FovChanger::Outer() {
        if (fovChangerHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void FovChanger::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("FOV (%.1f)", f_Fov.getValue());
    }

    std::string FovChanger::getModule() {
        return _("Misc");
    }

    void InLevelCameraSetFov_Hook(app::Camera* __this, float value) {
        auto& FovChanger = FovChanger::getInstance();
        bool enabled = FovChanger.f_Enabled.getValue();

        if (!enabled)
            return;

        value = enabled ? FovChanger.f_Fov.getValue() : 45.0f;
        CALL_ORIGIN(InLevelCameraSetFov_Hook, __this, value);
    }
}
