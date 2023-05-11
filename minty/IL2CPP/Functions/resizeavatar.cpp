#include "resizeavatar.h"

namespace il2fns {
	void Resize__Avatar(float scale) {
		app::Vector3 ResizingScale;
		app::GameObject* Avatar__Object = app::UnityEngine__GameObject__Find(il2cpp_string_new("/EntityRoot/AvatarRoot"));
		if (Avatar__Object == nullptr) {
			ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "No avatar found" });
		}
		else {
			app::Transform* Avatar__Transform = app::UnityEngine__Component__get__Transform(Avatar__Object);
			if (Avatar__Transform == nullptr) {
				ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "No component found" });
			}
			else {
				ResizingScale = { scale,scale,scale };
				app::UnityEngine__Transform__set__localScale(Avatar__Transform, ResizingScale);
			}
		}
	}
}