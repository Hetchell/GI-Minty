#include <string>
#include <unordered_map>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../ImGui/ImGui/imgui.h"

#include "../Games/games.h"

#include "../Functions/Misc/bootyfixer.h"
#include "../Functions/Misc/dialogskip.h"
#include "../Functions/World/dumbenemies.h"
#include "../Functions/Player/godmode.h"
#include "../Functions/Player/infinityenergy.h"
#include "../Functions/Player/infinitystamina.h"
#include "../Functions/Player/nocd.h"
#include "../Functions/Player/noclip.h"
#include "../Functions/Misc/uimisc.h"
#include "../Functions/Misc/unlockfps.h"
#include "../Functions/Player/multihit.h"
#include "../Functions/World/autotp.h"
#include "../Functions/Misc/cutsceneskip.h"
#include "../Functions/World/speedhack.h"
#include "../Functions/About/About.h"
#include "../Functions/Settings/Settings.h"

#include "../Lua/function.h"
#include "../Utils/GuiUtils.hpp"
#include "MainGUI.h"
#include "../ImGui/ImGuiNotify/imgui_notify.h"
#include "GuiDefinitions.h"
#include "../Config/ConfigManager.hpp"
#include "../Json/json.hpp"
#include "../Lua/luahook.hpp"
#include "../Utils/LuaUtils.hpp"
#include "../Utils/Utils.hpp"
#include "../Themes/Themes.hpp"


std::vector<std::string> ModuleOrder = {
    "Player",
    "World",
    "Misc",
    "About",
    "Settings"
};

void Init() {
    PUSH_FUNC(Peeking);
    PUSH_FUNC(CutsceneSkip);
    PUSH_FUNC(DialogSkip);
    PUSH_FUNC(UIMisc);
    PUSH_FUNC(UnlockFPS);
    PUSH_FUNC(Godmode);
    PUSH_FUNC(InfinityEnergy);
    PUSH_FUNC(InfStamina);
    PUSH_FUNC(MultiHit);
    PUSH_FUNC(NoCD);
    PUSH_FUNC(Noclip);
    PUSH_FUNC(DumbEnemies);
    PUSH_FUNC(Speedhack);
    PUSH_FUNC(About);
    PUSH_FUNC(Settings);
}

void Outer() {
    for (auto& func : All_vec) {
        __try {
            func->Outer();
        } __except(1) {}
    }
    /*std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    ifshowfps = config_json["general"]["ShowFPS"];
    if (ifshowfps) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("##FPS", NULL, flags);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }*/
}

void DrawSection(const std::string& sectionName) {
    for (auto& func : All_vec) {
        if (func->GetGroupName() != sectionName)
            continue;

        func->GUI();
    }
}
