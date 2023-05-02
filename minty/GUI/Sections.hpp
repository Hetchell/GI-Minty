#pragma once
#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"

#include "../Games/games.h"

#include "../IL2CPP/Functions/molemole.h"
#include "../IL2CPP/Functions/bootyfixer.h"
#include "../IL2CPP/Functions/timescale.h"

#include <string>
#include <unordered_map>
//#include "../IL2CPP/il2cpp-init.hpp"
#include "GuiDefinitions.h"
#include "../ImGui/ImGuiNotify/imgui_notify.h"
//#include "../ImGui/ImGuiNotify/tahoma.h"
//#include "../Lua/luahook.hpp"
#include "../Utils/Log.hpp"
#include "../Utils/something.h"

uintptr_t baseAddress1 = (uint64_t)GetModuleHandle("UserAssembly.dll");
uintptr_t unityPlayerAddress1 = (uint64_t)GetModuleHandle("UnityPlayer.dll");

std::vector<std::string> ModuleOrder = {
    "Player", 
    "World",
    "Minigames",
    "Themes",
    "Debug",
    "About",
    "Settings",
    "AAAAAAAAA HELP ME"
};

template <typename T>
const char* get_ptr1(const T& value) {
    std::stringstream ss;
    ss << std::hex << std::showbase << reinterpret_cast<const void*>(value);
    static std::string result = ss.str();
    return result.c_str();
}

namespace Sections {

    void Player() {
        ImGui::SeparatorText("Add separator text for each category of cheat here");

        if (ImGui::Button("MoleMole Message DEBUG")) {
            if (GetModuleHandle("UserAssembly.dll") != nullptr)
                il2fns::MoleMole__ActorUtils__ShowMessage("123");
            else
                //ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Hello World! This is an error! 0x%X", 0xDEADBEEF });
                ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Pointers are still NULLPTR." });
        }

        if (ImGui::Button("UA ptr debug")) {
            if (baseAddress1 == (uint64_t)nullptr) {
                util::log(1, "UA is still very not real, wait pwease qwq uwu");
                ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "UA is still very not real, wait pwease qwq uwu" });

                baseAddress1 = (uint64_t)GetModuleHandle("UserAssembly.dll");
                if (GetModuleHandle("UserAssembly.dll") != nullptr) {
                    util::log(2, "now ua ptr: %s", get_ptr1(baseAddress1));
                }
            }
            else {
                util::log(1, "first var of ptr is just getmodule: %s", get_ptr1(GetModuleHandle("UserAssembly.dll")));
                util::log(1, "second var of ptr is baseAddress from il2i: %s", get_ptr1(baseAddress1));
                util::log(1, "third var of ptr is just getmodule but goofy var: %s", get_ptr1(GetModuleHandleW(L"UserAssembly.dll")));
                ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "first var of ptr is just getmodule: %s", get_ptr1(GetModuleHandle("UserAssembly.dll") )});
                ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "second var of ptr is baseAddress from il2i: %s", get_ptr1(baseAddress1) });
                ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "third var of ptr is just getmodule but goofy var: %s", get_ptr1(GetModuleHandleW(L"UserAssembly.dll")) });
            }
        }

        if (ImGui::Button("Show MoleMole Avatar Pos")) {
            //luahookfunc("CS.MoleMole.ActorUtils.ShowMessage(\"eksdee xlua alive mhy suck\")");
            if (GetModuleHandle("UserAssembly.dll") != nullptr)
                il2fns::MoleMole__ActorUtils__GetAvatarPos();
            else
                //ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Hello World! This is an error! 0x%X", 0xDEADBEEF });
                ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Pointers are still NULLPTR." });
        }
    }

    static float TimeScale = 1.0f;
    void World() {
        ImGui::SeparatorText("Add separator text for each category of cheat here");

        if (ImGui::SliderFloat("Timescale", &TimeScale, 0.0f, 5.0f, "%.3f")) {
            il2fns::UnityEngine__set__Timescale(TimeScale);
        }

        ImGui::SameLine();
        HelpMarker("Changes speed of game time. Applies to everything in game.");

        ImGui::SameLine();
        if (ImGui::Button("Reset (F11)")) {
            TimeScale = 1.0;
            il2fns::UnityEngine__set__Timescale(TimeScale);
        }
    }

    void Minigames() {
        ImGui::SeparatorText("Wordle");
        wordle_main();

        ImGui::SeparatorText("Minesweeper");

        ImGui::SeparatorText("Tic-tac-toe");

        ImGui::SeparatorText("Lights out");
    }

    void About() {
        ImGui::SeparatorText("About");

        ImGui::Text("Minty version x.x.x");
        ImGui::Text("ImGui version: %s", ImGui::GetVersion());

        ImGui::Text("Game version: ???");
        ImGui::SameLine();
        ImGui::TextDisabled("maybe add version detector, compare and shit");

        ImGui::SeparatorText("");

        ImGui::Text("Minty Github: ");
        TextURL("Link", "https://github.com/kindawindytoday/minty", true, false);
        ImGui::Text("Minty Discord: ");
        TextURL("Link", "https://discord.gg/kindawindytoday", true, false);

        ImGui::SeparatorText("");

        ImGui::Text("asdasd add stuff");
    }

    void Themes() {
        ImGui::SeparatorText("Themes");
    
        ImGui::TextDisabled("Add stuff here... theme customizer etc choose dropdwn");

        ImGui::SeparatorText("Fonts");

        ImGui::TextDisabled("Add font selector dropdown, & ttf loader");

        // ImGui::BeginCombo(
        //     "Font", //Label
        //     NULL
        //     );

        //ImGui::ShowStyleEditor();
    }

    void Settings() {
        ImGui::Checkbox("Show ImGui's cursor", &ImGui::GetIO().MouseDrawCursor);
    }
    
    void Debug() {
        ImGui::SeparatorText("Debug");

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("Dear ImGui version: %s", ImGui::GetVersion());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        ImGui::SeparatorText("");

        ImGui::Checkbox("Show Debug Metrics", &show_debug_metrics);
        ImGui::Checkbox("Show Minty Debug Log", &show_debug_log);

        if(ImGui::Button("ptr"))
            util::log(2,"debug log ptr %s", get_ptr1(show_debug_metrics) );

    }

    void Booba() {
        ImGui::TextColored(ImVec4(255, 0, 0, 255), "IDK PLEASE HELP I HAVE EMOTION SWINGS AGAIN oh pizza");
    }

    //this will be ran regardless of the tab
    void Outer() {
        if(show_debug_metrics)
			ImGui::ShowMetricsWindow(&show_debug_metrics);
        
        if (show_debug_log) 
            ShowDebugLog();

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
    {"Debug", &Sections::Debug},
    {"AAAAAAAAA HELP ME", &Sections::Booba}
};

void DrawSection(const std::string& sectionName) {
    auto it = SectionMap.find(sectionName);
    if (it != SectionMap.end()) {
        Sections::Outer();
        it->second();
    } else {
       ImGui::TextDisabled("No section matches name");
    }
}
