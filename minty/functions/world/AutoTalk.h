#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class AutoTalk : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<float> f_TalkSpeed;

		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static AutoTalk& getInstance();

		void OnCutScenePageUpdate(app::InLevelCutScenePageContext* context);

		AutoTalk();
	};
}
