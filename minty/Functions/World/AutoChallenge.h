#pragma once

#include "../FunctionIncludes.h"
#include "../../game/filters.h"

namespace cheat {
    class AutoChallenge : public Function {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<float> f_Range;
        ConfigField<bool> f_BombDestroy;
        ConfigField<int> f_Delay;

        Hotkey f_Hotkey;

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string getModule() override;

        int64_t nextTime;

        static AutoChallenge& getInstance();

        AutoChallenge();
    };
}
