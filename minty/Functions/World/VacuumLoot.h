#pragma once

#include "../FunctionIncludes.h"
#include "../../game/filters.h"
#include "../../game/SimpleFilter.h"

namespace cheat {
    class VacuumLoot : public Function {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<int> f_Delay;
        ConfigField<float> f_Distance;
        ConfigField<float> f_Radius;

        ConfigField<bool> f_Ores;
        ConfigField<bool> f_OresDrop;
        ConfigField<bool> f_Oculies;
        ConfigField<bool> f_Plants;
        ConfigField<bool> f_Equipments;
        ConfigField<bool> f_ItemDrops;

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
