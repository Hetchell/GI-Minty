#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class About : public Function {
	public:
		void GUI() override;

		std::string getModule() override;

		static About& getInstance();
	};
}
