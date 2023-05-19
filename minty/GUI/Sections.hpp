#pragma once
//#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include "MainGUI.h"
#include "../Utils/GuiUtils.hpp"

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
#include "../IL2CPP/Functions/infinitystamina.h"
#include "../IL2CPP/Functions/godmode.h"
#include "../IL2CPP/Functions/browser.h"
#include "../IL2CPP/Functions/breastsizer.h"
#include "../IL2CPP/Functions/fovchanger.h"
#include "../IL2CPP/Functions/dumbenemies.h"
#include "../IL2CPP/Functions/dialogskip.h"

#include "../Lua/function.h"

#include <string>
#include <unordered_map>
//#include "../IL2CPP/il2cpp-init.hpp"
#include "GuiDefinitions.h"
#include "../ImGui/ImGuiNotify/imgui_notify.h"
//#include "../ImGui/ImGuiNotify/tahoma.h"
//#include "../Lua/luahook.hpp"
#include "../Utils/LuaUtils.hpp"
#include "../Utils/Utils.hpp"
#include "../Lua/luahook.h"
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
    "Lua Console",
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
        ImGui::SeparatorText("Debug");

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

            if (ImGui::SliderFloat("Avatar scale", &avatarsize, 0.0f, 25.0f, "%.3f")) {
                il2fns::Resize__Avatar(avatarsize);
            }

            ImGui::SameLine();

            if (ImGui::Button("reset")) {
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

        static bool ifInfStamina = false;
        if (ImGui::Checkbox("Infinity stamina", &ifInfStamina)) {
            if (ifInfStamina)
                il2fns::Infinity_Stamina(true);
            else
                il2fns::Infinity_Stamina(false);
        }

        static bool ifGodmode = false;
        if (ImGui::Checkbox("No fall damage", &ifGodmode)) {
            if (ifGodmode)
                il2fns::GodMode(true);
            else
                il2fns::GodMode(false);
        }

        static bool ifBreast = false;
        static float breastSize = 1;
        ImGui::Checkbox("Resize breast", &ifBreast);
        ImGui::SameLine();
        HelpMarker("Changes size of avatar's breasts.");
        if (ifBreast) {
            ImGui::Indent();
            if (ImGui::SliderFloat("Breast size", &breastSize, 0.0f, 50.0f, "%.3f")) {
                __try {
                    il2fns::ScaleBreast();
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {
                    util::log(2, "err 0x%08x", GetExceptionCode());
                }
            }

            ImGui::SameLine();
            HelpMarker("Changes size of avatar's breasts. Doesn't work on characters, that have no breasts. You understood me.");

            ImGui::SameLine();
            if (ImGui::Button("Reset")) {
                breastSize = 1.0;
                il2fns::ScaleBreast();
            }
            ImGui::Unindent();
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

        static bool isbrowser = false;
        static char browserUrlBuf[256] = "";
        static float browserSize = 1;
        if (ImGui::Checkbox("Browser", &isbrowser)) {
            if (!isbrowser)
                il2fns::TurnBrowser(false, 1, "");
        }
        ImGui::SameLine();
        HelpMarker("Creates interactive browser panel with defined scale and URL. use Alt+Mouse or Bow to interact.");
        if (isbrowser) {
            ImGui::Indent();

            ImGui::SliderFloat("Browser scale", &browserSize, 0.1f, 20.0f, "%.3f");
            ImGui::SameLine();
            HelpMarker("Set scale ratio of Browser. 1.0 - 1920x1080.");

            ImGui::InputTextWithHint("Browser URL", "Input Browser URL", browserUrlBuf, 256);

            if (ImGui::Button("Create")) {
                if (browserSize != 0 && strcmp(browserUrlBuf, "")) {
                    il2fns::TurnBrowser(true, browserSize, browserUrlBuf);
                }
            }
            ImGui::Unindent();
        }

        static bool ifDumbAI = false;
        if (ImGui::Checkbox("Dumb Enemies", &ifDumbAI)) {
            if (ifDumbAI)
                il2fns::DumbEnemies(true);
            else
                il2fns::DumbEnemies(false);
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
            il2fns::BootyFixer(ifpeeking);
        }
        ImGui::SameLine();
        HelpMarker(":3");

        static bool show_colorator3000 = false;
        static float cc_r = 1.0f;
        static float cc_g = 1.0f;
        static float cc_b = 1.0f;
        static float cc_a = 1.0f;
        static ImVec4 infusion_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        ImGui::Checkbox("Infusion changer", &show_colorator3000);
        ImGui::SameLine();
        HelpMarker("Changes color of Elemental Infusion/Blade trail of your current character. Adjust color either with sliders or with color picker. Works perfectly on swords, greatswords, polearms.");
        if (show_colorator3000)
        {
            ImGui::Indent();

            if (ImGui::Button("Change")) {
                std::string result = char_eleminf + std::to_string(cc_r) + "," + std::to_string(cc_g) + "," + std::to_string(cc_b) + "," + std::to_string(cc_a) + char_eleminf_end;
                lua_runstr(result.c_str());
            }
            ImGui::SameLine();

            ImGui::ColorEdit4("Infusion Color", &infusion_col.x, ImGuiColorEditFlags_AlphaBar);

            cc_r = infusion_col.x;
            cc_g = infusion_col.y;
            cc_b = infusion_col.z;
            cc_a = infusion_col.w;

            ImGui::Unindent();
        }

        static bool iffov = false;
        static float targetfov = 45;
        if (ImGui::Checkbox("Change FOV", &iffov)) {
            if (!iffov)
                il2fns::ChangeFov(45.0f);
        }
        ImGui::SameLine();
        HelpMarker("Changes camera Field Of View. (Default = 45.)");
        if (iffov) {
            ImGui::Indent();
            if (ImGui::SliderFloat("Target FOV", &targetfov, 10, 160))
                il2fns::ChangeFov(targetfov);                
            ImGui::Unindent();
        }

        static bool ifElem = false;
        if (ImGui::Checkbox("Infinity Elemental sight", &ifElem)) {
            il2fns::ElemSight(ifElem);
        }

        static bool ifDialog = false;
        if (ImGui::Checkbox("Auto-talk", &ifDialog)) {
            if (ifDialog)
                il2fns::DialogSkip(true);
            else
                il2fns::DialogSkip(false);
        }

        static bool ifCSC = false;
        if (ImGui::Checkbox("Skip cutscene", &ifCSC)) {
            if (ifCSC)
                il2fns::CutsceneSkip(true);
            else
                il2fns::CutsceneSkip(false);
        }
        //static bool ifChest = false;
        //if (ImGui::Checkbox("Show chest indicators", &ifChest)) {
        //    if (ifElem)
        //        il2fns::ChestIndicator(true);
        //    else
        //        il2fns::ChestIndicator(false);
        //}
       /* static bool ifOTI = false;
        if (ImGui::Checkbox("Open team immediately", &ifOTI)) {
            il2fns::OpenTeamImm(ifOTI);
        }*/
    }

    void LuaConsole() {

        static TextEditor editor;
        static bool initialized = false;

        if (!initialized)
        {
            editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
            editor.SetPalette(TextEditor::GetDarkPalette());

            editor.SetTabSize(4);
            editor.SetShowWhitespaces(false);
            editor.SetColorizerEnable(true);

            initialized = true;
        }

        if (ImGui::Button("Run"))
        {
            std::string code = editor.GetText();
            if (!code.empty() && code.find_first_not_of(" \t\n\v\f\r") != std::string::npos)
            {
                if (true) {
                    lua_runstr(code.c_str());
                    if (last_ret_code == 0) {
                        util::log(2, "compilation success: %s", last_tolstr);
                    }
                }
                else {
                    util::log(0, "Lua is not hooked", "");
                }
            }
        }
        ImGui::SameLine();
        //saver to button below.

        //static vector<pair<std::string, function<void()>>> buttonFuncs;
        static char buttonLabel[256] = "";

        if (ImGui::Button("Create new button")) {
            ImGui::OpenPopup("New button");
        }
        ImGui::SameLine();
        ImGui::Checkbox("Show log", &show_debug_log);

        if (ImGui::BeginPopup("New button")) {
            ImGui::InputText("Label", buttonLabel, 256);
            if (ImGui::Button("Create")) {
                std::string functionText = editor.GetText();
                std::function<void()> buttonFunc = [functionText]() {
                    lua_runstr(functionText.c_str());
                };
                //buttonFuncs.emplace_back(string(buttonLabel), buttonFunc);
                memset(buttonLabel, 0, sizeof(buttonLabel));
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        //ImGui::Begin("Minty");
        //for (const auto& button : buttonFuncs) {
        //    if (ImGui::Button(button.first.c_str())) {
        //        button.second();
        //    }
        //}
        //ImGui::End();

        if (ImGui::BeginMenuBar())
        {
            //ImGui::InputText("##path3", path3, sizeof(path3));
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load .lua file"))
                {
                }
                ImGui::EndMenu();
            }
            /*if (FileDialog::file_dialog_open) {
                FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, file_dialog_buffer, sizeof(file_dialog_buffer), FileDialog::file_dialog_open_type);
            }*/
            if (ImGui::BeginMenu("Edit"))
            {
                bool ro = editor.IsReadOnly();
                if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                    editor.SetReadOnly(ro);
                ImGui::Separator();

                if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
                    editor.Undo();
                if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
                    editor.Redo();

                ImGui::Separator();

                if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                    editor.Copy();
                if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
                    editor.Cut();
                if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
                    editor.Delete();
                if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                    editor.Paste();

                ImGui::Separator();

                if (ImGui::MenuItem("Select all", nullptr, nullptr))
                    editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Dark palette"))
                    editor.SetPalette(TextEditor::GetDarkPalette());
                if (ImGui::MenuItem("Light palette"))
                    editor.SetPalette(TextEditor::GetLightPalette());
                if (ImGui::MenuItem("Retro blue palette"))
                    editor.SetPalette(TextEditor::GetRetroBluePalette());
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        editor.Render("TextEditor");
    }
}

using DrawFunction = void(*)();

const std::unordered_map<std::string, DrawFunction> SectionMap = {
    {"Player", &Sections::Player},
    {"World", &Sections::World},
    {"Misc", &Sections::Misc},
    {"Lua Console", &Sections::LuaConsole},
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
