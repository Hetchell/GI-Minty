#include "../Function.h"
#include "../../Utils/GuiUtils.hpp"
#include "../../Config/ConfigManager.hpp"
#include "../../Themes/themes.hpp"

namespace cheat {
	class Settings : public FN {
	public:
		std::string groupName = "Settings";
		inline static bool ifShowFPS;
		inline static bool ifShowRPC;
		inline static int initDelay = 15;
		
		void GUI() override;
		void Outer() override;

		std::string GetGroupName() override {
			return groupName;
		}
	};
}