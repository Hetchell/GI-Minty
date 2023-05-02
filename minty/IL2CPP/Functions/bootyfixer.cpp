#include "bootyfixer.h"

namespace il2fns {
	void MoleMole__ActorUtils__GetAvatarPos() {
		void* avatarpos = app::MoleMole__ActorUtils__GetAvatarPos();
		app::MoleMole__ActorUtils__ShowMessage(avatarpos);
	}
}