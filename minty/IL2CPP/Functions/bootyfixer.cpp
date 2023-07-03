#include "bootyfixer.h"

static bool alpha;
static bool ifinit = false;
static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value)
{
    if (alpha)
        value = 1;
    CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, __this, value);
}

static void ondogacha(uint32_t count) {
    //app::SetGachaResult()
    util::log(M_Info, "blud literaly spent %i gems", 160 * count);
}

namespace il2fns {
    void BootyFixer() {
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinit) {     
            HookManager::install(app::OnDoGacha, ondogacha);
            HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue); ifinit = true;
        }

        static bool ifpeeking = readBoolFuncStateFromJson("Booty");
        alpha = ifpeeking;

        if (ImGui::Checkbox("Enable peeking", &ifpeeking)) {
            saveFuncStateToJson("Booty", ifpeeking);
            alpha = ifpeeking;
        }
        ImGui::SameLine();
        HelpMarker(";)");
    }
}