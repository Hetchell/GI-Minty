#pragma once

#include "../FunctionIncludes.h"
#include "../../game/filters.h"
#include "../../game/SimpleFilter.h"

namespace cheat {
    class MobVacuum : public Function {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<int> f_Delay;

        ConfigField<bool> f_IncludeMonsters;

        ConfigField<bool> f_MonsterCommon;
        ConfigField<bool> f_MonsterElites;
        ConfigField<bool> f_MonsterBosses;

        ConfigField<bool> f_IncludeAnimals;

        ConfigField<bool> f_AnimalDrop;
        ConfigField<bool> f_AnimalPickUp;
        ConfigField<bool> f_AnimalNPC;

        ConfigField<float> f_Speed;
        ConfigField<float> f_Radius;
        ConfigField<float> f_Distance;
        ConfigField<bool> f_OnlyTarget;
        ConfigField<bool> f_Instantly;
        ConfigField<bool> f_SetCollider;

        Hotkey f_Hotkey;

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string getModule() override;

        static MobVacuum& getInstance();
        int64_t nextTime;
        std::vector<game::IEntityFilter*> m_Filters;

        MobVacuum();
    };
}
