#include "bootyfixer.h"

static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOn(app::MoleMole_VCBaseSetDitherValue* __this, float value)
{
    value = 1;
    CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOn, __this, value);
}

static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOff(app::MoleMole_VCBaseSetDitherValue* __this, float value)
{
    value = 0;
    CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOff, __this, value);
}

namespace il2fns {
    void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(bool value) {
        if (value) {
            //HookManager::detach(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOff);
            HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOn);
        }
        else {
            HookManager::detach(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOn);
            HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValueOff);
        }
    }
}