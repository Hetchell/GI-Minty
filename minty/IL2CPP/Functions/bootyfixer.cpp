#include "bootyfixer.h"

static bool alpha;
static bool ifinit = false;
static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value)
{
    if (alpha)
        value = 1;
    CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, __this, value);
}

namespace il2fns {
    void BootyFixer() {
        //app::GameObject* waterPeeking = nullptr;

        //util::log(M_Info, "inWater: %d", app::Test_inDive);
        while (app::UnityEngine__GameObject__Find(string_to_il2cppi("EntityRoot/AvatarRoot")) && !ifinit) {
            HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue);
            //waterPeeking = app::UnityEngine__GameObject__Find(string_to_il2cppi("/EffectPool/Eff_Player_Diving_Root"));
            ifinit = true;
        }

        static bool ifpeeking = readBoolFuncStateFromJson("Booty");
        alpha = ifpeeking;

        if (ImGui::Checkbox("Enable peeking", &ifpeeking)) {
            saveFuncStateToJson("Booty", ifpeeking);
            alpha = ifpeeking;
        }
        ImGui::SameLine();
        HelpMarker(";)");

        /*
        while (ifpeeking && ifinit) {
            if (!waterPeeking) {
                util::log(M_Info, "waterPeeking == null");
                return;
            }

            /*if (!app::GameObject_get_active(waterPeeking))
                return;

            app::UnityEngine__GameObject__SetActive(waterPeeking, false);
        }*/
    }
}