#pragma once

#include "../Function.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class About : public FN {
	public:
		void GUI() override;

		std::string getModule() override;
	};
}
