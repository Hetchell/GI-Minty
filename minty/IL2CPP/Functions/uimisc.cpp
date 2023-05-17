#include "uimisc.h"

static bool ifElem;
static void LevelSceneElementViewPlugin_Tick_HookOn(app::LevelSceneElementViewPlugin* __this, float inDeltaTime) {
     __this->fields._triggerElementView = true;
    CALL_ORIGIN(LevelSceneElementViewPlugin_Tick_HookOn, __this, inDeltaTime);
}

static void LevelSceneElementViewPlugin_Tick_HookOff(app::LevelSceneElementViewPlugin* __this, float inDeltaTime) {
    CALL_ORIGIN(LevelSceneElementViewPlugin_Tick_HookOff, __this, inDeltaTime);
}

namespace il2fns {
	void Change_UID(const char* uidText) {
        app::GameObject* uidTextObj = app::UnityEngine__GameObject__Find(il2cpp_string_new("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        app::Component_1* uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, il2cpp_string_new("Text"));

		app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), il2cpp_string_new(uidText));
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