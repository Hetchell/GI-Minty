#include "hideui.h"

namespace il2fns {
	void Hide__UI(bool value) {
		app::GameObject* ui_camera = app::UnityEngine__GameObject__Find(il2cpp_string_new("/UICamera"));

		app::Component_1* ui_cameraComp = app::UnityEngine_GameObject_GetComponent(ui_camera, il2cpp_string_new("Camera"));
		reinterpret_cast<app::BaseComponentPlugin__Fields*>(ui_cameraComp)->_enabled = value;
	}
}