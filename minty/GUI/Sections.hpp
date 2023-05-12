#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"

#include "../Games/games.h"

#include "../IL2CPP/Functions/molemole.h"
#include "../IL2CPP/Functions/bootyfixer.h"
#include "../IL2CPP/Functions/timescale.h"
#include "../IL2CPP/Functions/unlockfps.h"
#include "../IL2CPP/Functions/resizeavatar.h"
#include "../IL2CPP/Functions/hideui.h"
#include "../IL2CPP/Functions/infinityenergy.h"
#include "../IL2CPP/Functions/nocd.h"
#include "../IL2CPP/Functions/uimisc.h"

#include <string>
#include <unordered_map>
//#include "../IL2CPP/il2cpp-init.hpp"
#include "GuiDefinitions.h"
#include "../ImGui/ImGuiNotify/imgui_notify.h"
//#include "../ImGui/ImGuiNotify/tahoma.h"
//#include "../Lua/luahook.hpp"
#include "../Utils/LuaUtils.hpp"
#include "../Utils/Utils.hpp"
#include "../Lua/luahook.hpp"
bool block_input = true;
bool show_debug_metrics = false;
bool show_debug_log = false;
uintptr_t baseAddress1 = (uint64_t)GetModuleHandleA("UserAssembly.dll");
uintptr_t unityPlayerAddress1 = (uint64_t)GetModuleHandleA("UnityPlayer.dll");

ImGuiID textureID = 0;

std::vector<std::string> ModuleOrder = {
    "Player", 
    "World",
    "Misc",
    "Minigames",
    "Themes",
    "Debug",
    "About",
    "Settings"
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
            if (GetModuleHandleA("UserAssembly.dll") != nullptr)
                il2fns::MoleMole__ActorUtils__ShowMessage("123");
            else
                ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Pointers are still NULLPTR." });
        }

        if (ImGui::Button("UA ptr debug")) {
            //luahookfunc("CS.MoleMole.ActorUtils.ShowMessage(\"Lua works btw\")");
            if (baseAddress1 == (uint64_t)nullptr) {
                util::log(1, "UA is still very not real, wait pwease qwq uwu");
                ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "UA is still very not real, wait pwease qwq uwu" });

                baseAddress1 = (uint64_t)GetModuleHandleA("UserAssembly.dll");
                if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
                    util::log(2, "now ua ptr: %s", get_ptr1(baseAddress1));
                }
            }
            else {
                util::log(1, "first var of ptr is just getmodule: %s", get_ptr1(GetModuleHandleA("UserAssembly.dll")));
                util::log(1, "second var of ptr is baseAddress from il2i: %s", get_ptr1(baseAddress1));
                util::log(1, "third var of ptr is just getmodule but goofy var: %s", get_ptr1(GetModuleHandleW(L"UserAssembly.dll")));
                ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "first var of ptr is just getmodule: %s", get_ptr1(GetModuleHandleA("UserAssembly.dll") )});
                ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "second var of ptr is baseAddress from il2i: %s", get_ptr1(baseAddress1) });
                ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "third var of ptr is just getmodule but goofy var: %s", get_ptr1(GetModuleHandleW(L"UserAssembly.dll")) });
            }
        }
        
        static bool show_avatarresizer = false;
        ImGui::Checkbox("Avatar resizer", &show_avatarresizer);
        ImGui::SameLine();
        HelpMarker("Resizes your current character's size. Just move slider. ");

        if (show_avatarresizer) {
            static float avatarsize = 1.0f;
            ImGui::Indent();

            if (ImGui::SliderFloat("Avatar scale", &avatarsize, 0.0f, 25.0f, "%.3f"))
            {
                il2fns::Resize__Avatar(avatarsize);
            }

            ImGui::SameLine();

            if (ImGui::Button("reset"))
            {
                il2fns::Resize__Avatar(1.0f);
            }

            ImGui::Unindent();
        }

        static bool ifEnergy = false;
        if (ImGui::Checkbox("Infinity burst energy", &ifEnergy)) {
            if (ifEnergy)
                il2fns::Infinity__Energy(true);
            else
                il2fns::Infinity__Energy(false);
        }

        static bool ifNOCD = false;
        if (ImGui::Checkbox("No skill cooldown", &ifNOCD)) {
            if (ifNOCD)
                il2fns::LCAvatarCombat_NoCD(true);
            else
                il2fns::LCAvatarCombat_NoCD(false);
        }
    }

    static float TimeScale = 1.0f;
    void World() {
        ImGui::SeparatorText("Add separator text for each category of cheat here");

        static bool timescale = false;
        ImGui::Checkbox("Change time speed", &timescale);
        ImGui::SameLine();
        HelpMarker("Unlocks your framerate to defined target FPS.");
        if (timescale) {
            ImGui::Indent();
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
            ImGui::Unindent();
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

        static bool ifEditor;
        ImGui::Checkbox("show theme editor", &ifEditor);

        if (ifEditor) {
            ImGui::ShowStyleEditor();
        }

        // ImGui::BeginCombo(
        //     "Font", //Label
        //     NULL
        //     );

        //ImGui::ShowStyleEditor();
    }
    void Settings() {
        ImGui::Checkbox("Show ImGui's cursor", &ImGui::GetIO().MouseDrawCursor);
       
        ImGui::Checkbox("Block input", &block_input);
    }
    
    void Debug() {
        ImGui::SeparatorText("Debug");

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("Dear ImGui version: %s", ImGui::GetVersion());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        ImGui::SeparatorText("Status");
        const char* hook_state_name[] = {"not hooked", "hooked"};
        ImVec4 hooked_name_color[] = {ImVec4( 0.76078f, 0.219607f, 0.219607f, 1), ImVec4( 0.12156f, 0.8f, 0.2f, 1.0f)};
        ImGui::Text("il2cpp: "); ImGui::SameLine(); ImGui::TextColored(hooked_name_color[0], hook_state_name[0]); //placeholder values
        ImGui::Text("Lua: "); ImGui::SameLine(); ImGui::TextColored(hooked_name_color[1], hook_state_name[1]); //put std to string boolean here, it will give a 1 or a zero 

        ImGui::SeparatorText("");
   
        ImGui::Checkbox("Show Debug Metrics", &show_debug_metrics);
        ImGui::Checkbox("Show Minty Debug Log", &show_debug_log);

        ImGui::SeparatorText("mDumper");

        static char defind[256] = "";
        static char getnam[256] = "";
        static char getmed[256] = "";
        static char gentyp[256] = "";
        ImGui::InputText("defind", defind, 256);
        ImGui::InputText("getnam", getnam, 256);
        ImGui::InputText("getmed", getmed, 256);
        ImGui::InputText("gentyp", gentyp, 256);

        if (ImGui::Button("scan patterns")) {
            //util::log(2, "defind is: %s", util::int_to_hex(util::PatternScan("UserAssembly.dll", (LPCSTR)defind)));
            //util::log(2, "getnam is: %s", util::int_to_hex(util::PatternScan("UserAssembly.dll", (LPCSTR)getnam)));
            //util::log(2, "getmed is: %s", util::int_to_hex(util::PatternScan("UserAssembly.dll", (LPCSTR)getmed)));
            //util::log(2, "gentyp is: %s", util::int_to_hex(util::PatternScan("UserAssembly.dll", (LPCSTR)gentyp)));
        }

        if (ImGui::Button("init mdumper ptrs")) {
            //init_mD(defind, getnam, getmed, gentyp);
        }

    }

    //this will be ran regardless of the tab
    void Outer() {
        if(show_debug_metrics)
			ImGui::ShowMetricsWindow(&show_debug_metrics);
        
        if (show_debug_log) 
            ShowDebugLog();

    }

    void Misc() {
        //bool misc1 = false;
        //float misc1;
        //CreateFuncWidget("It is label of checkbox, that shows/hides slider.", misc1, "It is HelpMarker text", "some slider name", misc1, 60, 10, 100, il2fns::UnityEngine__set__Timescale);
        static bool unlockfps = false;
        static int targetfps = 60;
        if(ImGui::Checkbox("Unlock FPS", &unlockfps)) {
            if (!unlockfps)
                il2fns::UnityEngine__Application__set_targetFramerate(60);
        }
        ImGui::SameLine();
        HelpMarker("Unlocks your framerate to defined target FPS.");
        if (unlockfps) {
            ImGui::Indent();
            // ImGui::SliderFloat("Target FPS", &targetfps, 10.0f, 360.0f, "%.3f");

            ImGui::SliderInt("Target FPS",&targetfps, 1, 360);

            static float fpsunlocktimer = 0.0f;
            fpsunlocktimer += ImGui::GetIO().DeltaTime;
            if (fpsunlocktimer > 1.0f) {
                il2fns::UnityEngine__Application__set_targetFramerate(targetfps);
                fpsunlocktimer = 0;
            }
            ImGui::Unindent();
        }

        static bool hideui = false;
        if (ImGui::Checkbox("Hide UI", &hideui)) {
            if (hideui) {
                il2fns::Hide__UI(false);
            }
            else {
                il2fns::Hide__UI(true);
            }
        }
        ImGui::SameLine();
        HelpMarker("Hides all game UI.");

        static char UID_inputTextBuffer[512] = "";
        ImGui::InputTextWithHint("##input", "Enter custom UID text here...", UID_inputTextBuffer, sizeof(UID_inputTextBuffer));
        ImGui::SameLine();
        if (ImGui::Button("Update custom UID")) {
            il2fns::Change_UID(UID_inputTextBuffer);
        }
        ImGui::SameLine();
        HelpMarker("Changes your game UID to any defined text. HTML/Rich Text tags can be applied.");

        static bool ifpeeking = false;
        if (ImGui::Checkbox("Enable peeking", &ifpeeking)) {
            if (ifpeeking) {
                il2fns::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(true);
            }
            else {
                il2fns::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(false);
            }
        }
        ImGui::SameLine();
        HelpMarker(":3");
    }
}

using DrawFunction = void(*)();

const std::unordered_map<std::string, DrawFunction> SectionMap = {
    {"Player", &Sections::Player},
    {"World", &Sections::World},
    {"Misc", &Sections::Misc},
    {"Minigames", &Sections::Minigames},
    {"About", &Sections::About},
    {"Themes", &Sections::Themes},
    {"Settings", &Sections::Settings},
    {"Debug", &Sections::Debug}
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
