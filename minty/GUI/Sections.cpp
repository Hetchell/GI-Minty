#include <unordered_map>

//#include "../Games/games.h"

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
    INIT_FUNC(ProfileChanger);

    PUSH_FUNC(About);

    PUSH_FUNC(AutoTalk);
    //PUSH_FUNC(CameraZoom);
    PUSH_FUNC(CutsceneSkip);
    PUSH_FUNC(FovChanger);
    //PUSH_FUNC(OpenTeamImmediately);
    PUSH_FUNC(Peeking);
    PUSH_FUNC(ProfileChanger);
    PUSH_FUNC(ShowChestIndicator);
    //PUSH_FUNC(SkipEnhanceAnimation);
    PUSH_FUNC(UnlockFPS);

    PUSH_FUNC(GodMode);
    PUSH_FUNC(InfinityEnergy);
    PUSH_FUNC(InfinityStamina);
    PUSH_FUNC(MultiHit);
    //PUSH_FUNC(NoClip);
    PUSH_FUNC(NoCooldown);

    PUSH_FUNC(Settings);

    //PUSH_FUNC(AutoTP);
    PUSH_FUNC(DumbEnemies);
    //PUSH_FUNC(GameSpeed);
}

void Outer() {
    for (auto& func : All_vec) {
        __try {
            func->Outer();
        } __except(1) {}
    }
}

void DrawSection(const std::string& moduleName) {
    for (auto& func : All_vec) {
        if (func->getModule() != moduleName)
            continue;

        func->GUI();
    }
}
