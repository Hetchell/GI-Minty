#include "hideui.h"

namespace il2fns {
	void Hide__UI(bool value) {
		//app::UnityEngine__GameObject__SetActive(app::UnityEngine__GameObject__Find(il2cpp_string_new("/UICamera")), value);
		app::CameraEntity* uiCam = (app::CameraEntity*)app::UnityEngine__GameObject__Find(il2cpp_string_new("/UICamera"));
		uiCam->fields.bef._isActive = value;
	}
}