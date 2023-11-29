#pragma once

#include "../FunctionIncludes.h"
#include "../../game/filters.h"

namespace cheat {
    class VacuumLoot : public Function {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<int> f_Delay;
        ConfigField<float> f_Distance;
        ConfigField<float> f_Radius;

        Hotkey f_Hotkey;

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string getModule() override;

        static VacuumLoot& getInstance();
        int64_t nextTime;

        VacuumLoot();
    };
}
