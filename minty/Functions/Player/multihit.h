#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class MultiHit : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<int> f_Hits;

		inline static Hotkey multiHitHotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static MultiHit& getInstance();

		MultiHit();
	};
}
