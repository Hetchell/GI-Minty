#pragma once
#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"

#include "../Games/games.h"

#include <string>
#include <unordered_map>

std::vector<std::string> ModuleOrder = {
    "Player", 
    "World",
    "Minigames",
    "Themes",
    "About",
    "Settings",
    "Testing"
};

namespace Sections {
    void Player() {
        ImGui::Text("Player Section");

        if(ImGui::CollapsingHeader("## cock hack")) {
            ImGui::Text("sob");
        }
    }

    void World() {
        ImGui::Text("World section");
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
    {"Testing", &Sections::Testing}
};

void DrawSection(const std::string& sectionName) {
    auto it = SectionMap.find(sectionName);
    if (it != SectionMap.end()) {
        it->second();
    } else {
       ImGui::TextDisabled("No section matches name");
    }
}
