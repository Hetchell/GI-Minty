#include "resizeavatar.h"

namespace il2fns {
	void Resize__Avatar(float scale) {
		void* Avatar__Object = app::UnityEngine__GameObject__Find(il2cpp_string_new("/EntityRoot/AvatarRoot"));
		LPVOID Avatar__Transform = app::UnityEngine__Component__get__Transform(Avatar__Object);
		Vector3 ResizingScale = { scale, scale, scale };
		app::UnityEngine__Transform__set__localScale(Avatar__Transform, ResizingScale);
	}
}