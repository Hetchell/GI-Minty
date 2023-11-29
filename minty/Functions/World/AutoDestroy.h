#pragma once

#include "../FunctionIncludes.h"
#include "../../game/filters.h"

namespace cheat {
    class AutoDestroy : public Function {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<float> f_Range;

        ConfigField<bool> f_DestroyOres;
        ConfigField<bool> f_DestroyShields;
        ConfigField<bool> f_DestroyDoodads;
        ConfigField<bool> f_DestroyPlants;
        ConfigField<bool> f_DestroySpecialObjects;
        ConfigField<bool> f_DestroySpecialChests;


        Hotkey f_Hotkey;

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string getModule() override;

        static AutoDestroy& getInstance();

        AutoDestroy();
    };
}
