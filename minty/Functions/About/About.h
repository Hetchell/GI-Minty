#pragma once

#include "../Function.h"
#include "../../Utils/GuiUtils.hpp"

namespace cheat {
	class About : public Function {
	public:
		void GUI() override;

		std::string getModule() override;
	};
}
