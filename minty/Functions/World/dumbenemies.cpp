#include "dumbenemies.h"

namespace cheat {
    static void VCMonsterAIController_TryDoSkill_Hook(void* __this, uint32_t skillID)
    {
        if (DumbEnemies::ifDumbEnemies)
            return;
        CALL_ORIGIN(VCMonsterAIController_TryDoSkill_Hook, __this, skillID);
    }
    
    DumbEnemies::DumbEnemies() {
        HookManager::install(app::MoleMole_VCMonsterAIController_TryDoSkill, VCMonsterAIController_TryDoSkill_Hook);
    }

    void DumbEnemies::Status() {
        if (DumbEnemies::ifDumbEnemies) {
            ImGui::Text(_("Dumb enemies"));
        }
    }

    void DumbEnemies::GUI() {
        ImGui::Checkbox("Dumb Enemies", &DumbEnemies::ifDumbEnemies)) {
        HelpMarker("Make enemies have the same level of intelligence as Congress.");
    }

    void DumbEnemies::Outer() {
        if (dumbEnemiesHotkey.IsPressed())
            ifDumbEnemies = !ifDumbEnemies;
    }
}