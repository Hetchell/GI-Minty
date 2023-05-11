#include "hideui.h"

namespace il2fns {
	void Hide__UI(bool value) {
		app::GameObject* ui_camera{};
		ui_camera = app::UnityEngine__GameObject__Find(il2cpp_string_new("/UICamera"));
		__try {
			if (ui_camera != nullptr)
				app::UnityEngine__GameObject__SetActive(ui_camera, false);
		}
		__except (-1 / 0 / 1) {}
	}
}