#include "hideui.h"

app::GameObject* camObj;
namespace il2fns {
	void Hide__UI(bool value) {
		camObj = app::UnityEngine__GameObject__Find(il2cpp_string_new("UICamera"));
		if (camObj != nullptr) {
			if (camObj->fields._.m_CachedPtr != nullptr) {
				app::UnityEngine__GameObject__SetActive(camObj, value);
			}
		}
		else {
			util::log(2, "cam not found");
		}
	}
}