#include "uimisc.h"

static bool ifElem;
static void LevelSceneElementViewPlugin_Tick_HookOn(app::LevelSceneElementViewPlugin* __this, float inDeltaTime) {
     __this->fields._triggerElementView = true;
    CALL_ORIGIN(LevelSceneElementViewPlugin_Tick_HookOn, __this, inDeltaTime);
}

static void LevelSceneElementViewPlugin_Tick_HookOff(app::LevelSceneElementViewPlugin* __this, float inDeltaTime) {
    __this->fields._triggerElementView = false;
    CALL_ORIGIN(LevelSceneElementViewPlugin_Tick_HookOff, __this, inDeltaTime);
}

static bool ifChest;
static bool IndicatorPlugin_DoCheckOn(app::LCIndicatorPlugin* __this) {
    if (__this->fields._dataItem != nullptr)
    {
        app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
    }
    return CALL_ORIGIN(IndicatorPlugin_DoCheckOn, __this);
}

static bool IndicatorPlugin_DoCheckOff(app::LCIndicatorPlugin* __this) {
    return CALL_ORIGIN(IndicatorPlugin_DoCheckOff, __this);
}

namespace il2fns {
	void Change_UID(const char* uidText) {
        app::GameObject* uidTextObj = app::UnityEngine__GameObject__Find(il2cpp_string_new("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        app::Component_1* uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, il2cpp_string_new("Text"));

		app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), il2cpp_string_new(uidText));
	}

    void ChestIndicator(bool value) {
        if (value) {
            if (ifChest) {
                HookManager::detach(IndicatorPlugin_DoCheckOff);
                ifChest = false;
            }
            HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheckOn);
        }
        else {
            HookManager::detach(IndicatorPlugin_DoCheckOn);
            HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheckOff);
            ifChest = true;
        }
    }

    void ElemSight(bool value) {
        if (value) {
            if (ifElem) {
                HookManager::detach(LevelSceneElementViewPlugin_Tick_HookOff);
                ifElem = false;
            }
            HookManager::install(app::MoleMole_LevelSceneElementViewPlugin_Tick, LevelSceneElementViewPlugin_Tick_HookOn);
        }
        else {
            HookManager::detach(LevelSceneElementViewPlugin_Tick_HookOn);
            HookManager::install(app::MoleMole_LevelSceneElementViewPlugin_Tick, LevelSceneElementViewPlugin_Tick_HookOff);
            ifElem = true;
        }
    }
}