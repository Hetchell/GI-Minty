#pragma once

#include "../Function.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class About : public FN {
	public:
		std::string groupName = "About";

		void GUI() override;

		std::string GetGroupName() override {
			return groupName;
		}

		//About();
	};
}