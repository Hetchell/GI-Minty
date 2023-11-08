#include "ShowChestIndicator.h"

namespace cheat {
    bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this);

    ShowChestIndicator::ShowChestIndicator() {
        f_Enabled = config::getValue("functions:ShowChestIndicator", "enabled", false);
        f_Hotkey = Hotkey("functions:ShowChestIndicator");

        HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck);
    }

    ShowChestIndicator& ShowChestIndicator::getInstance() {
        static ShowChestIndicator instance;
        return instance;
    }

    void ShowChestIndicator::GUI() {
        ConfigCheckbox("Show Chest Indicator", f_Enabled, "Show chests, game mechanics.");

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            f_Hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void ShowChestIndicator::Outer() {
        if (f_Hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void ShowChestIndicator::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Show Chest Indicator");
    }

    std::string ShowChestIndicator::getModule() {
        return _("Visuals");
    }

    bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
        auto& showChestIndicator = ShowChestIndicator::getInstance();

        if (showChestIndicator.f_Enabled.getValue()) {
            //if (__this->fields._dataItem != nullptr)
                app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
        } else
            app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
        return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
    }
}
