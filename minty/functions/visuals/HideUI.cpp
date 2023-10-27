#include "HideUI.h"

namespace cheat {
    static void onUpdate_4(app::GameManager* __this, app::MethodInfo* method);

    HideUI::HideUI() : Function() {
        f_Enabled = config::getValue("functions:HideUI", "enabled", false);
        f_Hotkey = Hotkey("functions:HideUI");

        HookManager::install(app::GameManager_Update, onUpdate_4);
    }

    HideUI& HideUI::getInstance() {
        static HideUI instance;
        return instance;
    }

    void HideUI::GUI() {
        ConfigCheckbox("Hide UI", f_Enabled, "Hide in-game UI.");

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            f_Hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void HideUI::Outer() {
        if (f_Hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void HideUI::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Hide UI");
    }

    std::string HideUI::getModule() {
        return _("Visuals");
    }

    app::GameObject* ui_camera{};
    void onUpdate_4(app::GameManager* __this, app::MethodInfo* method) {
        auto& hideUI = HideUI::getInstance();

        if (hideUI.f_Enabled.getValue()) {
            if (ui_camera == nullptr)
                ui_camera = app::GameObject_Find(string_to_il2cppi("/UICamera"));

            if (ui_camera->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(ui_camera, false);
        } else {
            if (ui_camera) {
                if (ui_camera->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(ui_camera, true);

                ui_camera = nullptr;
            }
        }
        CALL_ORIGIN(onUpdate_4, __this, method);
    }
}
