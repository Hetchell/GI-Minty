#include "ShowChestIndicator.h"

namespace cheat {
    static bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this);

    ShowChestIndicator::ShowChestIndicator() {
        f_Enabled = config::getValue("functions:ShowChestIndicator", "enabled", false);
    }

    ShowChestIndicator& ShowChestIndicator::getInstance() {
        static ShowChestIndicator instance;
        return instance;
    }

    void ShowChestIndicator::GUI() {
        ConfigCheckbox("Show chest indicators", f_Enabled);

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            chestIndicHotkey.Draw();
            ImGui::Unindent();
        }
    }

    void ShowChestIndicator::Outer() {
        if (chestIndicHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void ShowChestIndicator::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Show Chest Indicators");
    }

    std::string ShowChestIndicator::getModule() {
        return _("Misc");
    }

    static bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
        auto& ShowChestIndicator = ShowChestIndicator::getInstance();

        if (ShowChestIndicator.f_Enabled.getValue()) {
            if (__this->fields._dataItem != nullptr)
                app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
        } else
            app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
        return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
    }
}
