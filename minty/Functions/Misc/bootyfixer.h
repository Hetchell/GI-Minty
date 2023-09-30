#include "../il2cpp-appdata.h"
#include "../HookManager.h"
#include "../il2cpp-types.h"
#include "../Function.h"

namespace cheat {
	class Peeking : public FN {
	public:
		inline static bool ifPeeking;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string groupName() override;

		Peeking();
	};
}
