#include "bootyfixer.h"

static bool alpha;
static bool ifinit;
static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value)
{
    if (alpha)
        value = 1;
    CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, __this, value);
}

namespace il2fns {
    void BootyFixer(bool value) {
        if (!ifinit)
            HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue); ifinit = true;
        alpha = value;
    }
}