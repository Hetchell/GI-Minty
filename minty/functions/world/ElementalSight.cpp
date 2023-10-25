#include "ElementalSight.h"

namespace cheat {
    static void LevelSceneElementViewPlugin_Tick_Hook(app::LevelSceneElementViewPlugin* __this, float inDeltaTime);

    ElementalSight::ElementalSight() : Function() {
        f_Enabled = config::getValue("functions:ElementalSight", "enabled", false);
        
        HookManager::install(app::MoleMole_LevelSceneElementViewPlugin_Tick, LevelSceneElementViewPlugin_Tick_Hook);
    }

    ElementalSight& ElementalSight::getInstance() {
        static ElementalSight instance;
        return instance;
    }

    void ElementalSight::GUI() {
        ConfigCheckbox("Permanent Elemental Sight", f_Enabled, "Elemental sight is kept on even when moving.\n"
                     "To turn off, toggle off and use Elemental Sight again.");

        if (f_Enabled.getValue()) {
            ImGui::Indent();
            hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void ElementalSight::Outer() {
        if (hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void ElementalSight::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Elemental Sight");
    }

    std::string ElementalSight::getModule() {
        return _("World");
    }

    void LevelSceneElementViewPlugin_Tick_Hook(app::LevelSceneElementViewPlugin* __this, float inDeltaTime) {
        auto& elementalSight = ElementalSight::getInstance();

        if (!elementalSight.f_Enabled.getValue())
            return;

        LOG_DEBUG("_triggerElementView: %d", __this->fields._triggerElementView);
        __this->fields._triggerElementView = true;
        CALL_ORIGIN(LevelSceneElementViewPlugin_Tick_Hook, __this, inDeltaTime);
    }
}
