#include "hideui.h"

namespace il2fns {
	void Hide__UI(bool value) {
		app::GameObject* camObj = app::UnityEngine__GameObject__Find(il2cpp_string_new("/UICamera"));
		auto camComp = app::UnityEngine_GameObject_GetComponent(camObj, il2cpp_string_new("Camera"));
		reinterpret_cast<app::CameraEntity__Fields*>(camComp)->bef._isActive = value;
		reinterpret_cast<app::BaseComponent*>(camComp)->fields._enabled = value;
	}
}