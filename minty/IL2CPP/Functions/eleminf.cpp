#include "eleminf.h"

namespace il2fns {
	void Infusion_Color(int color) {
		app::GameObject* effectPoolObj = app::UnityEngine__GameObject__Find((app::String*)il2cpp_string_new("/EffectPool"));

		int cEf = app::UnityEngine_Transform_GetChildCount(app::UnityEngine__Component__get__Transform(effectPoolObj));

		for (int cEf = app::UnityEngine_Transform_GetChildCount(app::UnityEngine__Component__get__Transform(effectPoolObj)); cEf--;) {
			app::Transform* childEf = app::UnityEngine_Transform_GetChild(app::UnityEngine__Component__get__Transform(effectPoolObj), cEf);
		}
	}
}