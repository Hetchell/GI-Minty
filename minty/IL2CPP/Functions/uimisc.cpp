#include "uimisc.h"

namespace il2fns {
	void Change_UID(const char* uidText) {
        app::GameObject* uidTextObj = app::UnityEngine__GameObject__Find(il2cpp_string_new("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        app::Component_1* uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, il2cpp_string_new("Text"));

		app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), il2cpp_string_new(uidText));
	}
}