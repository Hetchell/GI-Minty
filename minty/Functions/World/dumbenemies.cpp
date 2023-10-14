#include "DumbEnemies.h"

namespace cheat {
    static void VCMonsterAIController_TryDoSkill_Hook(void* __this, uint32_t skillID);
    
    DumbEnemies::DumbEnemies() {
        f_Enabled = config::getValue("functions:DumbEnemies", "enabled", false);

        HookManager::install(app::MoleMole_VCMonsterAIController_TryDoSkill, VCMonsterAIController_TryDoSkill_Hook);
    }

    DumbEnemies& DumbEnemies::getInstance() {
        static DumbEnemies instance;
        return instance;
    }

    void DumbEnemies::Status() {
        if (f_Enabled.getValue())
            ImGui::Text(_("Dumb enemies"));
    }

    void DumbEnemies::GUI() {
        ConfigCheckbox("Dumb Enemies", f_Enabled);
        ImGui::SameLine();
        HelpMarker("Enemies don't attack or use abilities against player.\n"
            "May not work with some enemies or enemy abilities.");
    }

    void DumbEnemies::Outer() {
        if (dumbEnemiesHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    std::string DumbEnemies::getModule() {
        return _("World");
    }

    void VCMonsterAIController_TryDoSkill_Hook(void* __this, uint32_t skillID) {
        auto& DumbEnemies = DumbEnemies::getInstance();

        if (DumbEnemies.f_Enabled.getValue())
            return;

        CALL_ORIGIN(VCMonsterAIController_TryDoSkill_Hook, __this, skillID);
    }
}
