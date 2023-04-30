#pragma once
#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"

#include "../Games/games.h"

#include "../IL2CPP/Functions/molemole.h"
#include "../IL2CPP/Functions/bootyfixer.h"
//#include "../IL2CPP/Functions/timescale.h"

#include <string>
#include <unordered_map>
//#include "../IL2CPP/il2cpp-init.hpp"

uintptr_t baseAddress1 = (uint64_t)GetModuleHandle("UserAssembly.dll");
uintptr_t unityPlayerAddress1 = (uint64_t)GetModuleHandle("UnityPlayer.dll");

std::vector<std::string> ModuleOrder = {
    "Player", 
    "World",
    "Minigames",
    "Themes",
    "About",
    "Settings",
    "Testing",
    "AAAAAAAAA HELP ME"
};

namespace Sections {
    void Player() {
        ImGui::Text("Player Section");

        if(ImGui::CollapsingHeader("## cock hack")) {
            ImGui::Text("sob");
        }

        if (ImGui::Button("MoleMole Message DEBUG")) {
            il2fns::MoleMole__ActorUtils__ShowMessage("123");
        }


        if (ImGui::Button("UA ptr debug")) {

            while (baseAddress1 == (uint64_t)nullptr)
            {
                util::log(1, "UA is still very not real");
                Sleep(1000);
                baseAddress1 = (uint64_t)GetModuleHandle("UserAssembly.dll");
                if (GetModuleHandle("UserAssembly.dll") != nullptr) {
                    util::log(2, "now ua ptr: %p", baseAddress1);
                }
            }

            util::log(1, "first var of ptr is just getmodule: %p", GetModuleHandle("UserAssembly.dll"));
            util::log(1, "second var of ptr is baseAddress from il2i: %p", baseAddress1);
            util::log(1, "third var of ptr is just getmodule but goofy var: %p", GetModuleHandleW(L"UserAssembly.dll"));
        }
    }

    static float TimeScale = 1;
    void World() {
        ImGui::Text("World section");

        if (ImGui::SliderFloat("Timescale", &TimeScale, 0.0f, 5.0f, "%.3f"))
        {
            //il2fns::UnityEngine__Time__TimeScale(TimeScale);
        }
        ImGui::SameLine();
        HelpMarker("Changes speed of game time. Applies to everything in game.");

        ImGui::SameLine();
        if (ImGui::Button("Reset (F11)")) {
            TimeScale = 1.0f;
            //il2fns::UnityEngine__Time__TimeScale(TimeScale);
        }

        ImGui::Text("here is");
        TextURL("Minty Guthibbe", "https://github.com/kindawindytoday/minty", true, false);
    }

    void Minigames() {
        ImGui::SeparatorText("Wordle");
        wordle_main();

        ImGui::SeparatorText("Minesweeper");

        ImGui::SeparatorText("Tic-tac-toe");

        ImGui::SeparatorText("Lights out");
    }

    void About() {}

    void Themes() {}

    void Settings() {}

    void Booba() {
        ImGui::TextColored(ImVec4(255, 0, 0, 255), "IDK PLEASE HELP I HAVE EMOTION SWINGS AGAIN oh pizza");
    }
    
    void Testing() {
        ImGui::Button("AddCockHere");
    }
}


using DrawFunction = void(*)();

const std::unordered_map<std::string, DrawFunction> SectionMap = {
    {"Player", &Sections::Player},
    {"World", &Sections::World},
    {"Minigames", &Sections::Minigames},
    {"About", &Sections::About},
    {"Themes", &Sections::Themes},
    {"Settings", &Sections::Settings},
    {"Testing", &Sections::Testing},
    {"AAAAAAAAA HELP ME", &Sections::Booba}
};

void DrawSection(const std::string& sectionName) {
    auto it = SectionMap.find(sectionName);
    if (it != SectionMap.end()) {
        it->second();
    } else {
       ImGui::TextDisabled("No section matches name");
    }
}
