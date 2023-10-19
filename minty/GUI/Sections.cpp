#include "../Functions/About/About.h"

#include "../Functions/Misc/AutoTalk.h"
#include "../Functions/Misc/CameraZoom.h"
#include "../Functions/Misc/CutsceneSkip.h"
#include "../Functions/Misc/FovChanger.h"
#include "../Functions/Misc/OpenTeamImmediately.h"
#include "../Functions/Misc/Peeking.h"
#include "../Functions/Misc/ProfileChanger.h"
#include "../Functions/Misc/ShowChestIndicator.h"
#include "../Functions/Misc/SkipEnhanceAnimation.h"
#include "../Functions/Misc/UnlockFPS.h"

#include "../Functions/Player/GodMode.h"
#include "../Functions/Player/InfinityEnergy.h"
#include "../Functions/Player/InfinityStamina.h"
#include "../Functions/Player/MultiHit.h"
#include "../Functions/Player/NoClip.h"
#include "../Functions/Player/NoCooldown.h"

#include "../Functions/Settings/Settings.h"

#include "../Functions/World/AutoTP.h"
#include "../Functions/World/DumbEnemies.h"
#include "../Functions/World/GameSpeed.h"

std::vector<std::string> ModuleOrder = {
    "Player",
    "World",
    "Misc",
    "About",
    "Settings"
};

void Init() {
    INIT_FUNC(About);

    INIT_FUNC(AutoTalk);
    INIT_FUNC(CameraZoom);
    INIT_FUNC(CutsceneSkip);
    INIT_FUNC(FovChanger);
    //INIT_FUNC(OpenTeamImmediately);
    INIT_FUNC(Peeking);
    INIT_FUNC(ProfileChanger);
    INIT_FUNC(ShowChestIndicator);
    INIT_FUNC(SkipEnhanceAnimation);
    INIT_FUNC(UnlockFPS);

    INIT_FUNC(GodMode);
    INIT_FUNC(InfinityEnergy);
    INIT_FUNC(InfinityStamina);
    INIT_FUNC(MultiHit);
    INIT_FUNC(NoClip);
    INIT_FUNC(NoCooldown);

    INIT_FUNC(Settings);

    //INIT_FUNC(AutoTP);
    INIT_FUNC(DumbEnemies);
    INIT_FUNC(GameSpeed);
}

void Outer() {
    for (auto& func : functions)
        func->Outer();
}

void DrawSection(const std::string& moduleName) {
    for (auto& func : functions) {
        if (func->getModule() != moduleName)
            continue;

        func->GUI();
    }
}
