#include "fovchanger.h"

static float fovValue;

void InLevelCameraSetFov_Hook(app::Camera* __this, float value)
{
    //value = fovValue;
    value = 90;
    CALL_ORIGIN(InLevelCameraSetFov_Hook, __this, value);
}

namespace il2fns {
    void ChangeFov(float value) {
        //fovValue = value;
        HookManager::install(app::Camera_set_fieldOfView, InLevelCameraSetFov_Hook);
    }
}