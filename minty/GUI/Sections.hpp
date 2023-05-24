#pragma once
// #define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <string>
#include <unordered_map>

#include "../Games/games.h"
#include "../IL2CPP/Functions/bootyfixer.h"
#include "../IL2CPP/Functions/breastsizer.h"
#include "../IL2CPP/Functions/browser.h"
#include "../IL2CPP/Functions/dialogskip.h"
#include "../IL2CPP/Functions/dumbenemies.h"
#include "../IL2CPP/Functions/fovchanger.h"
#include "../IL2CPP/Functions/godmode.h"
#include "../IL2CPP/Functions/hideui.h"
#include "../IL2CPP/Functions/infinityenergy.h"
#include "../IL2CPP/Functions/infinitystamina.h"
#include "../IL2CPP/Functions/molemole.h"
#include "../IL2CPP/Functions/nocd.h"
#include "../IL2CPP/Functions/noclip.h"
#include "../IL2CPP/Functions/resizeavatar.h"
#include "../IL2CPP/Functions/timescale.h"
#include "../IL2CPP/Functions/uimisc.h"
#include "../IL2CPP/Functions/unlockfps.h"
#include "../Lua/function.h"
#include "../Utils/GuiUtils.hpp"
#include "MainGUI.h"
// #include "../IL2CPP/il2cpp-init.hpp"
#include "../ImGui/ImGuiNotify/imgui_notify.h"
#include "GuiDefinitions.h"
// #include "../ImGui/ImGuiNotify/tahoma.h"
#include "../Config/ConfigManager.hpp"
#include "../Json/json.hpp"
#include "../Lua/luahook.hpp"
// #include "../Lua/luahook.h"
#include "../Utils/LuaUtils.hpp"
#include "../Utils/Utils.hpp"
// bool block_input = true;
// bool show_debug_metrics = false;
// bool show_debug_log = false;
// #include "../Lua/luavars.h"
#include "../Themes/themes.hpp"

uintptr_t baseAddress1 = (uint64_t)GetModuleHandleA("UserAssembly.dll");
uintptr_t unityPlayerAddress1 = (uint64_t)GetModuleHandleA("UnityPlayer.dll");

ImGuiID textureID = 0;

extern bool is_lua_hooked;
// extern bool is_il2cpp_hooked;
std::vector<std::string> lua_list;
std::string last_lua_string;

std::vector<std::string> ModuleOrder = {
    /*
    Text will generally be obfuscated with xorstr with the intent of making it harder for miHoYo to reverse engineer, and to prevent clout chasers,
    malware developers, etc. from modifying this app and distributing a malicious/rebranded version
    */
    /*xorstr_*/ ("Player"),
    /*xorstr_*/ ("World"),
    /*xorstr_*/ ("Misc"),
    /*xorstr_*/ ("Lua"),
    /*xorstr_*/ ("Minigames"),
    /*xorstr_*/ ("Themes"),
    ///*xorstr_*/("Debug"),
    /*xorstr_*/ ("About"),
    /*xorstr_*/ ("Settings")};

namespace Sections {

void Player() {
    ImGui::SeparatorText(/*xorstr_*/ ("Avatar"));

    /*
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
                util::log(2, "now ua ptr: %s", util::get_ptr(baseAddress1));
            }
        }
        else {
            util::log(1, "first var of ptr is just getmodule: %s", util::get_ptr(GetModuleHandleA("UserAssembly.dll")));
            util::log(1, "second var of ptr is baseAddress from il2i: %s", util::get_ptr(baseAddress1));
            util::log(1, "third var of ptr is just getmodule but goofy var: %s", util::get_ptr(GetModuleHandleW(L"UserAssembly.dll")));
            ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "first var of ptr is just getmodule: %s", util::get_ptr(GetModuleHandleA("UserAssembly.dll") )});
            ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "second var of ptr is baseAddress from il2i: %s", util::get_ptr(baseAddress1) });
            ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "third var of ptr is just getmodule but goofy var: %s", util::get_ptr(GetModuleHandleW(L"UserAssembly.dll")) });
        }
    }
    */

    // static bool show_avatarresizer = false;
    // ImGui::Checkbox(/*xorstr_*/("Avatar resizer"), &show_avatarresizer);
    // ImGui::SameLine();
    // HelpMarker(/*xorstr_*/("Resizes your current character's size."));

    // if (show_avatarresizer) {
    //     static float avatarsize = 1.0f;
    //     ImGui::Indent();

    //    if (ImGui::SliderFloat("Avatar scale", &avatarsize, 0.0f, 25.0f, "%.3f")) {
    //        il2fns::Resize__Avatar(avatarsize);
    //    }

    //    ImGui::SameLine();

    //    if (ImGui::Button("reset")) {
    //        il2fns::Resize__Avatar(1.0f);
    //    }

    //    ImGui::Unindent();
    //}

    ImGui::SeparatorText("Skills");

    static bool ifEnergy = false;
    if (ImGui::Checkbox("Infinity burst energy", &ifEnergy)) {
        saveFuncStateToJson("InfBurst", ifEnergy);
        il2fns::Infinity__Energy(ifEnergy);
    } ImGui::SameLine(); HelpMarker("Ignore energy level and allow elemental burst at any time.");

    static bool ifNOCD = false;
    if (ImGui::Checkbox("No skill cooldown", &ifNOCD)) {
        saveFuncStateToJson("NoCD", ifNOCD);
        il2fns::LCAvatarCombat_NoCD(ifNOCD);
    } ImGui::SameLine(); HelpMarker("Disable skill cooldowns.");

    static bool ifInfStamina = false;
    if (ImGui::Checkbox("Infinity stamina", &ifInfStamina)) {
        saveFuncStateToJson("InfStamina", ifInfStamina);
        il2fns::Infinity_Stamina(ifInfStamina);
    } ImGui::SameLine(); HelpMarker("Infinite stamina values.");

    static bool ifGodmode = false;
    if (ImGui::Checkbox("No fall damage", &ifGodmode)) {
        saveFuncStateToJson("NoFallDmg", ifGodmode);
        il2fns::GodMode(ifGodmode);
    } ImGui::SameLine(); HelpMarker("Take no damage after falling from any height.");

    // static bool ifBreast = false;
    // static float breastSize = 1;
    // ImGui::Checkbox("Resize breast", &ifBreast);
    // ImGui::SameLine();
    // HelpMarker("Changes size of avatar's breasts.");
    // if (ifBreast) {
    //     ImGui::Indent();
    //     if (ImGui::SliderFloat("Breast size", &breastSize, 0.0f, 50.0f, "%.3f")) {
    //         il2fns::ScaleBreast();
    //     }

    //    ImGui::SameLine();
    //    HelpMarker("Changes size of avatar's breasts. Doesn't work on characters, that have no breasts. You understood me.");

    //    ImGui::SameLine();
    //    if (ImGui::Button("Reset")) {
    //        breastSize = 1.0;
    //        il2fns::ScaleBreast();
    //    }
    //    ImGui::Unindent();
    //}

    static bool ifnobowcd;
    if (ImGui::Checkbox("Instant bow charge", &ifnobowcd)) {
        saveFuncStateToJson("InstantBow", ifnobowcd);
        il2fns::NoBowCD(ifnobowcd);
    } ImGui::SameLine(); HelpMarker("Instant elemental charge for bows.");

    // static bool ifnoclip = false;
    // if (ImGui::Checkbox("Noclip", &ifnoclip)) {
    //     saveFuncStateToJson("Noclip", ifnoclip);
    //     il2fns::OnNoclip(ifnoclip);
    // }

    static bool show_modelswap = false;
    if (ImGui::Checkbox("Model swapper", &show_modelswap)) {} ImGui::SameLine(); HelpMarker("Swaps your avatars' models. Press Clone to copy current avatar, press paste to apply the original avatar's model onto the current.");
    if (show_modelswap) {
        ImGui::Indent();

        if (ImGui::Button("Clone model")) {
            last_lua_string = char_modelswap_clone;
        }
        if (ImGui::Button("Paste model")) {
            last_lua_string = char_modelswap_paste;
        }
        ImGui::Unindent();
    }

    static bool show_resizer = false;
    static float boob_size = 1.0f;
    ImGui::Checkbox("Booba resizer", &show_resizer);
    ImGui::SameLine();
    HelpMarker("Changes size of character breasts. Press Initiate and adjust slider.");
    if (show_resizer) {
        ImGui::Indent();
        if (ImGui::Button("Initiate resize")) {
            boob_size = 1.0f;
            last_lua_string = char_bub_initiate;
        }

        ImGui::SameLine();

        if (ImGui::SliderFloat("Booba scale", &boob_size, 0.0f, 4.0f, "%.3f")) {
            std::string result = char_bub_resize + std::to_string(boob_size) + "," + std::to_string(boob_size) + "," + std::to_string(boob_size) + ")";
            last_lua_string = result;
        }
        ImGui::Unindent();
    }

    static bool animcheng = false;
    static int anim_select_index = 0;
    ImGui::Checkbox("Animation Changer", &animcheng);
    ImGui::SameLine();
    HelpMarker("Change current avatar's animation.");
    if (animcheng) {
        ImGui::Indent();
        if (ImGui::Combo("Animations", &anim_select_index, animation_options, IM_ARRAYSIZE(animation_options))) {
        }

        if (ImGui::Button("Change")) {
            std::string result = animchanger + std::string(animation_options[anim_select_index]) + animchanger2;
            last_lua_string = result;
        }
        if (ImGui::Button("Reset")) {
            last_lua_string = animchangerreturn;
        }
        ImGui::Unindent();
    }

    static bool emocheng = false;
    static int emo_select_index = 0;
    static int pho_select_index = 0;
    ImGui::Checkbox("Emotion Changer", &emocheng);
    ImGui::SameLine();
    HelpMarker("Change current avatar's emotion.");
    if (emocheng) {
        ImGui::Indent();
        if (ImGui::Combo("Face expression", &emo_select_index, emo_options, IM_ARRAYSIZE(emo_options))) {
        }
        if (ImGui::Combo("Mouth expression", &pho_select_index, pho_options, IM_ARRAYSIZE(pho_options))) {
        }

        if (ImGui::Button("Change")) {
            std::string result = emochengemo1 + std::string(emo_options[emo_select_index]) + emochengemo2 + std::string(pho_options[emo_select_index]) + emochengpho2;
            last_lua_string = result;
        }
    }

    static bool show_avatarresizer = false;
    ImGui::Checkbox("Avatar resizer", &show_avatarresizer);
    ImGui::SameLine();
    HelpMarker("Resizes your current character's size.");

    if (show_avatarresizer) {
        static float avatarsize = 1.0f;
        ImGui::Indent();
        std::string result = char_avatarresize + std::to_string(avatarsize) + "," + std::to_string(avatarsize) + "," + std::to_string(avatarsize) + ")";

        if (ImGui::SliderFloat("Avatar scale", &avatarsize, 0.0f, 25.0f, "%.3f")) {
            last_lua_string = result;
        }

        ImGui::SameLine();

        if (ImGui::Button("reset")) {
            std::string result = std::string(char_avatarresize) + "1 , 1, 1)";
            avatarsize = 1.0f;
            last_lua_string = result;
        }

        ImGui::Unindent();
    }
}

static float TimeScale = 1.0f;
void World() {
    ImGui::SeparatorText("World");

    static bool timescale = false;
    ImGui::Checkbox("Change time speed", &timescale);
    ImGui::SameLine();
    HelpMarker("Changes the speed at which the game runs.");
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

    // static bool isbrowser = false;
    // static char browserUrlBuf[256] = "";
    // static float browserSize = 1;

    // if (ImGui::Checkbox("Browser", &isbrowser)) {
    //     if (!isbrowser)
    //         il2fns::TurnBrowser(false, 1, "");
    // }

    // ImGui::SameLine();
    // HelpMarker("Creates interactive browser panel with defined scale and URL. use Alt+Mouse or Bow to interact.");

    // if (isbrowser) {
    //     ImGui::Indent();

    //    ImGui::SliderFloat("Browser scale", &browserSize, 0.1f, 20.0f, "%.3f");
    //    ImGui::SameLine();
    //    HelpMarker("Set scale ratio of Browser. 1.0 - 1920x1080.");

    //    ImGui::InputTextWithHint("Browser URL", "Input Browser URL", browserUrlBuf, 256);

    //    if (ImGui::Button("Create")) {
    //        if (browserSize != 0 && strcmp(browserUrlBuf, "")) {
    //            il2fns::TurnBrowser(true, browserSize, browserUrlBuf);
    //        }
    //    }

    //    ImGui::Unindent();
    //}

    static bool isbrowser = false;
    static char browserUrlBuf[256] = "";
    static float browserSize = 1;

    if (ImGui::Checkbox("Browser", &isbrowser)) {
        if (!isbrowser)
            il2fns::TurnBrowser(false, 1, "");
    } ImGui::SameLine(); HelpMarker("Creates an interactive web browser in the world.");

    // ImGui::SameLine();
    // HelpMarker("Creates interactive browser panel with defined scale and URL. use Alt+Mouse or Bow to interact.");

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
        saveFuncStateToJson("DumbEnemy", ifDumbAI);
        il2fns::DumbEnemies(ifDumbAI);
    } ImGui::SameLine(); HelpMarker("Make enemies have the same level of intelligence as Congress.");
}

void Minigames() {
    ImGui::SeparatorText("Wordle");
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6.00f, 6.00f));
    wordle_main();
    ImGui::PopStyleVar(2);

    // ImGui::SeparatorText("Minesweeper");

    // ImGui::SeparatorText("Tic-tac-toe");

    // ImGui::SeparatorText("Lights out");
}

void About() {
    ImGui::SeparatorText("About");

    ImGui::Text("Minty version 1.0.0");
    ImGui::Text("ImGui version: %s", ImGui::GetVersion());

    // ImGui::Text("Game version: ???");
    // ImGui::SameLine();
    // ImGui::TextDisabled("maybe add version detector, compare and shit");

    ImGui::SeparatorText("");

    ImGui::Text(/*xorstr_*/ ("Minty Github: "));
    TextURL(/*xorstr_*/ ("Link"), /*xorstr_*/ ("https://github.com/kindawindytoday/minty"), true, false);

    ImGui::Text(/*xorstr_*/ ("Minty Discord: "));
    TextURL(/*xorstr_*/ ("Link"), /*xorstr_*/ ("https://discord.gg/kindawindytoday"), true, false);

    ImGui::SeparatorText("");

    // ImGui::Text("asdasd add stuff");
}

void Themes() {
    ImGui::SeparatorText(/*xorstr_*/ ("Theme colors"));
    /*----------PLACEHOLDER----------*/
    static int themeIndex = 0;

    if (ImGui::RadioButton(/*xorstr_*/ ("Default dark"), &themeIndex, 0)) {
        settheme(1);
    }

    if (ImGui::RadioButton(/*xorstr_*/ ("Default light"), &themeIndex, 1)) {
        settheme(2);
    }

    if (ImGui::RadioButton(/*xorstr_*/ ("Default classic"), &themeIndex, 2)) {
        settheme(3);
    }

    if (ImGui::RadioButton(/*xorstr_*/ ("Dark theme"), &themeIndex, 3)) {
        settheme(4);
    }

    if (ImGui::RadioButton(/*xorstr_*/ ("Minty Red"), &themeIndex, 4)) {
        settheme(5);
    }

    if (ImGui::RadioButton(/*xorstr_*/ ("Minty Mint"), &themeIndex, 5)) {
        settheme(6);
    }

    if (ImGui::RadioButton(/*xorstr_*/ ("Minty Mint Light"), &themeIndex, 6)) {
        settheme(7);
    }

    ImGui::SeparatorText("Theme styles");

    static int themestyleindex = 0;

    if (ImGui::RadioButton(/*xorstr_*/ ("Minty"), &themestyleindex, 0)) {
        setstyle(1);
    }

    if (ImGui::RadioButton("Big", &themestyleindex, 1)) {
        setstyle(2);
    }

    if (ImGui::RadioButton("ImGui Default", &themestyleindex, 2)) {
        setstyle(3);
    }

    if (ImGui::RadioButton("Big Squared", &themestyleindex, 3)) {
        setstyle(4);
    }

    if (ImGui::RadioButton("Rounded Compact", &themestyleindex, 4)) {
        setstyle(5);
    }

    ImGui::SeparatorText("Fonts");

    static int fontSelectionIndex = 0;
    if (ImGui::RadioButton("idk", &fontSelectionIndex, 0)) {
        setfont(1);
    }

    if (ImGui::RadioButton("idk2", &fontSelectionIndex, 1)) {
        setfont(2);
    }

    ImGui::SeparatorText("Custom styles");
    ImGui::TextDisabled("DEBUG");
    ImGui::Checkbox("Show Style Editor", &show_style_editor);
    /*----------PLACEHOLDER----------*/
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
    ImVec4 hooked_name_color[] = {ImVec4(0.76078f, 0.219607f, 0.219607f, 1), ImVec4(0.12156f, 0.8f, 0.2f, 1.0f)};

    // ImGui::Text("il2cpp: ");
    // ImGui::SameLine();
    // ImGui::TextColored(hooked_name_color[static_cast<int>(is_il2cpp_hooked)], hook_state_name[static_cast<int>(is_il2cpp_hooked)]);
    // ImGui::Text("Lua: ");
    // ImGui::SameLine();
    // ImGui::TextColored(hooked_name_color[static_cast<int>(is_lua_hooked)], hook_state_name[static_cast<int>(is_lua_hooked)]);

    /*----------TEMP----------*/

    ImGui::SeparatorText("");

    ImGui::Checkbox("Show Debug Metrics", &show_debug_metrics);
    ImGui::Checkbox(/*xorstr_*/ ("Show Minty Debug Log"), &show_debug_log);

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
        util::log(M_Debug, "defind is: %p", PatternScan("UserAssembly.dll", (LPCSTR)defind));
        util::log(M_Debug, "defind is: %s", PatternScan("UserAssembly.dll", (LPCSTR)defind));
        util::log(M_Debug, "defind is: %i", PatternScan("UserAssembly.dll", (LPCSTR)defind));
        // util::log(2, "getnam is: %s", util::int_to_hex(util::PatternScan("UserAssembly.dll", (LPCSTR)getnam)));
        // util::log(2, "getmed is: %s", util::int_to_hex(util::PatternScan("UserAssembly.dll", (LPCSTR)getmed)));
        // util::log(2, "gentyp is: %s", util::int_to_hex(util::PatternScan("UserAssembly.dll", (LPCSTR)gentyp)));
    }

    if (ImGui::Button("init mdumper ptrs")) {
        // init_mD(defind, getnam, getmed, gentyp);
    }
}

// this will be ran regardless of the tab

void Misc() {
    // bool misc1 = false;
    // float misc1;
    // CreateFuncWidget("It is label of checkbox, that shows/hides slider.", misc1, "It is HelpMarker text", "some slider name", misc1, 60, 10, 100, il2fns::UnityEngine__set__Timescale);
    ImGui::SeparatorText("Rendering");

    static bool unlockfps = false;
    static int targetfps = 60;
    if (ImGui::Checkbox("Unlock FPS", &unlockfps)) {
        if (!unlockfps)
            il2fns::UnityEngine__Application__set_targetFramerate(60);
    }
    ImGui::SameLine();
    HelpMarker("Unlocks your framerate to defined target FPS.");
    if (unlockfps) {
        ImGui::Indent();
        // ImGui::SliderFloat("Target FPS", &targetfps, 10.0f, 360.0f, "%.3f");

        if (ImGui::SliderInt("Target FPS", &targetfps, 1, 360))
            saveFuncStateToJson("FPS", targetfps);

        static float fpsunlocktimer = 0.0f;
        fpsunlocktimer += ImGui::GetIO().DeltaTime;
        if (fpsunlocktimer > 1.0f) {
            il2fns::UnityEngine__Application__set_targetFramerate(targetfps);
            fpsunlocktimer = 0;
        }
        ImGui::Unindent();
    }

    // auto state = luaL_newstate();
    // static int threthr = 1;
    // if (ImGui::Button("lua molmol L")) {
    //     get_gi_L();
    //     util::log(M_Info, "thread is: %i", GetCurrentThreadId());
    //     //luahookfunc("CS.MoleMole.ActorUtils.ShowMessage(\"\123\")", gi_L);
    // }
    // if (ImGui::Button("lua molmol LL")) {
    //     util::log(M_Info, "thread is: %i", GetCurrentThreadId());
    //     //luahookfunc("CS.MoleMole.ActorUtils.ShowMessage(\"\123\")", gi_LL);
    // }
    // ImGui::SliderInt("Target ID", &threthr, 1, 50000);
    // if (ImGui::Button("lua molmol STATE")) {
    //     //util::log(M_Info, "main_thread is: %i", GetThreadId(mainluathread));
    //     auto thrthr = OpenThread(THREAD_ALL_ACCESS, false, threthr);
    //     util::log(M_Info, "main_thread is: %i", GetThreadId(thrthr));
    //     luahookfunc("CS.MoleMole.ActorUtils.ShowMessage(\"\123\")");
    // }
    // if (ImGui::Button("PUSHDFDBNFYDHFGEUIRHUIEGH"))
    //     last_lua_string = "CS.MoleMole.ActorUtils.ShowMessage(\"11111Lua pulled from lua_list vector\")";
    //    //lua_list.push_back("CS.MoleMole.ActorUtils.ShowMessage(\"Lua pulled from lua_list vector\")");

    static bool hideui = false;

    if (ImGui::Checkbox("Hide UI", &hideui)) {
        if (hideui) {
            last_lua_string = char_uicamera_off;
        } else {
            last_lua_string = char_uicamera_on;
        }
    } ImGui::SameLine(); HelpMarker("Toggles visibility of the game's UI.");

    static char UID_inputTextBuffer[512] = "";
    static bool ifUid;
    ImGui::Checkbox("Custom UID", &ifUid);
    ImGui::SameLine();
    HelpMarker("Changes your game UID to any defined string. HTML/Rich Text tags can be applied.");
    if (ifUid) {
        ImGui::InputTextWithHint("##input", "Enter custom UID text here...", UID_inputTextBuffer, sizeof(UID_inputTextBuffer));
        ImGui::SameLine();
        if (ImGui::Button("Update custom UID")) {
            std::string result = R"MY_DELIMITER(CS.UnityEngine.GameObject.Find("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"):GetComponent("Text").text = ")MY_DELIMITER" + std::string(UID_inputTextBuffer) + "\"";
            last_lua_string = result;
        }
    }

    static bool ifpeeking = false;
    if (ImGui::Checkbox("Enable peeking", &ifpeeking)) {
        saveFuncStateToJson("Booty", ifpeeking);
        il2fns::BootyFixer(ifpeeking);
    }
    ImGui::SameLine();
    HelpMarker("\"Uncensors\" the camera, so that you can freely look up characters' pants. This is a highly necessary feature in high demand (^_^)");

    static bool show_colorator3000 = false;
    static float cc_r = 1.0f;
    static float cc_g = 1.0f;
    static float cc_b = 1.0f;
    static float cc_a = 1.0f;
    static ImVec4 infusion_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    ImGui::Checkbox("Infusion changer", &show_colorator3000);
    ImGui::SameLine();
    HelpMarker("Changes color of Elemental Infusion/Blade trail of your current character. Adjust color either with sliders or with color picker. Works perfectly on swords, greatswords, polearms.");
    if (show_colorator3000) {
        ImGui::Indent();

        if (ImGui::Button("Change")) {
            std::string result = char_eleminf + std::to_string(cc_r) + "," + std::to_string(cc_g) + "," + std::to_string(cc_b) + "," + std::to_string(cc_a) + char_eleminf_end;
            last_lua_string = result;
        }
        ImGui::SameLine();

        ImGui::ColorEdit4("Infusion Color", &infusion_col.x, ImGuiColorEditFlags_AlphaBar);

        cc_r = infusion_col.x;
        cc_g = infusion_col.y;
        cc_b = infusion_col.z;
        cc_a = infusion_col.w;

        ImGui::Unindent();
    }

    ImGui::SeparatorText("Camera");

    // static bool iffov = false;
    // static float targetfov = 45;
    // if (ImGui::Checkbox("Change FOV", &iffov)) {
    //     if (!iffov)
    //         il2fns::ChangeFov(45.0f);
    // }
    // ImGui::SameLine();
    // HelpMarker("Changes camera Field Of View. (Default = 45.)");
    // if (iffov) {
    //     ImGui::Indent();
    //     if (ImGui::SliderFloat("Target FOV", &targetfov, 10, 160))
    //         il2fns::ChangeFov(targetfov);
    //     saveFuncStateToJson("FOV", targetfov);
    //     ImGui::Unindent();
    // }

    static bool ifElem = false;
    if (ImGui::Checkbox("Infinity Elemental sight", &ifElem)) {
        saveFuncStateToJson("ElemSight", ifElem);
        il2fns::ElemSight(ifElem);
    } ImGui::SameLine(); HelpMarker("Infinite duration for Elemental Sight.");

    static bool ifDialog = false;
    if (ImGui::Checkbox("Auto-talk", &ifDialog)) {
        saveFuncStateToJson("AutoTalk", ifDialog);
        il2fns::DialogSkip(ifDialog);
    } ImGui::SameLine(); HelpMarker("Automatically goes through dialogue.");

    static bool ifCSC = false;
    if (ImGui::Checkbox("Skip cutscene", &ifCSC)) {
        saveFuncStateToJson("CutsceneSkip", ifCSC);
        il2fns::CutsceneSkip(ifCSC);
    } ImGui::SameLine(); HelpMarker("Skip video cutscenes.");

    // static bool ifChest = false;
    // if (ImGui::Checkbox("Show chest indicators", &ifChest)) {
    //     if (ifElem)
    //         il2fns::ChestIndicator(true);
    //     else
    //         il2fns::ChestIndicator(false);
    // }
    /* static bool ifOTI = false;
    if (ImGui::Checkbox("Open team immediately", &ifOTI)) {
        il2fns::OpenTeamImm(ifOTI);
    }*/

    static bool ifzoom = false;
    static float targetzoom = 1;
    if (ImGui::Checkbox("Change Camera Zoom", &ifzoom)) {
        if (!ifzoom)
            il2fns::CameraZoom(1.0);
    } ImGui::SameLine(); HelpMarker("Changes the distance the camera is to the avatar.");

    ImGui::SameLine();
    HelpMarker("Changes camera Field Of View. (Default = 45)");
    if (ifzoom) {
        ImGui::Indent();
        if (ImGui::SliderFloat("Target Zoom", &targetzoom, -10, 500))
            il2fns::CameraZoom(targetzoom);
        saveFuncStateToJson("CameraZoom", targetzoom);
        ImGui::Unindent();
    }
}

void Lua() {
    ImGui::SeparatorText("Editor");
    ImGui::Checkbox("Show Lua editor", &show_lua_editor);

    if (ImGui::Button("XLua Hotfix")) {
        last_lua_string = xluaHotFix;
    }
}

void Outer() {
    if (show_debug_metrics)
        ImGui::ShowMetricsWindow(&show_debug_metrics);

    if (show_debug_log)
        ShowDebugLog();

    /*----------PLACEHOLDER----------*/
    if (show_style_editor) {
        ImGui::Begin("Style Editor", &show_style_editor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }
    /*----------PLACEHOLDER----------*/

    if (show_lua_editor) {
        ImGui::Begin("Lua editor", &show_lua_editor, ImGuiWindowFlags_MenuBar);
        static TextEditor editor;
        static bool initialized = false;

        if (!initialized) {
            editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
            editor.SetPalette(TextEditor::GetDarkPalette());

            editor.SetTabSize(4);
            editor.SetShowWhitespaces(false);
            editor.SetColorizerEnable(true);

            initialized = true;
        }

        if (ImGui::Button("Run")) {
            std::string code = editor.GetText();
            if (!code.empty() && code.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
                if (true) {  // if (is_lua_hooked) {
                    try {
                        auto thred = OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());
                        last_lua_string = code;
                    } catch (...) {
                        util::log(M_Error, "lua excep");
                    }
                    /*if (last_ret_code == 0) {
                        util::log(M_Info, "compilation success: %s", last_tolstr);
                    }*/
                } else {
                    ImGui::InsertNotification({ImGuiToastType_Error, 3000, "Lua is not hooked."});
                    util::log(M_Error, "Lua is not hooked");
                }
            }
        }
        ImGui::SameLine();
        // saver to button below.
        static char buttonLabel[256] = "";

        // if (ImGui::Button("Create new button")) {
        //     ImGui::OpenPopup("New button");
        // }
        ImGui::SameLine();
        ImGui::Checkbox("Show log", &show_debug_log);

        // if (ImGui::BeginPopup("New button")) {
        //     ImGui::InputText("Label", buttonLabel, 256);
        //     if (ImGui::Button("Create")) {
        //         std::string functionText = editor.GetText();
        //         std::function<void()> buttonFunc = [functionText]() {
        //             lua_runstr(functionText.c_str());
        //         };
        //         //buttonFuncs.emplace_back(string(buttonLabel), buttonFunc);
        //         memset(buttonLabel, 0, sizeof(buttonLabel));
        //         ImGui::CloseCurrentPopup();
        //     }
        //     ImGui::EndPopup();
        // }

        if (ImGui::BeginMenuBar()) {
            // ImGui::InputText("##path3", path3, sizeof(path3));
            if (ImGui::BeginMenu("File")) {
                // if (ImGui::MenuItem("Load .lua file")) {
                // }
                ImGui::TextDisabled("Nothing here...");
                ImGui::EndMenu();
            }
            /*if (FileDialog::file_dialog_open) {
                FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, file_dialog_buffer, sizeof(file_dialog_buffer), FileDialog::file_dialog_open_type);
            }*/
            if (ImGui::BeginMenu("Edit")) {
                bool ro = editor.IsReadOnly();
                if (ImGui::MenuItem("Read-only mode", nullptr, &ro)) editor.SetReadOnly(ro);
                ImGui::Separator();

                if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo())) editor.Undo();
                if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo())) editor.Redo();

                ImGui::Separator();

                if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection())) editor.Copy();
                if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection())) editor.Cut();
                if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection())) editor.Delete();
                if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr)) editor.Paste();

                ImGui::Separator();

                if (ImGui::MenuItem("Select all", nullptr, nullptr)) editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Dark palette")) editor.SetPalette(TextEditor::GetDarkPalette());
                if (ImGui::MenuItem("Light palette")) editor.SetPalette(TextEditor::GetLightPalette());
                if (ImGui::MenuItem("Retro blue palette")) editor.SetPalette(TextEditor::GetRetroBluePalette());
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        editor.Render("TextEditor");
        ImGui::End();
    }
}
}  // namespace Sections

using DrawFunction = void (*)();

const std::unordered_map<std::string, DrawFunction> SectionMap = {
    {/*xorstr_*/ ("Player"), &Sections::Player},
    {/*xorstr_*/ ("World"), &Sections::World},
    {/*xorstr_*/ ("Misc"), &Sections::Misc},
    {/*xorstr_*/ ("Lua"), &Sections::Lua},
    {/*xorstr_*/ ("Minigames"), &Sections::Minigames},
    {/*xorstr_*/ ("About"), &Sections::About},
    {/*xorstr_*/ ("Themes"), &Sections::Themes},
    {/*xorstr_*/ ("Settings"), &Sections::Settings},
    {/*xorstr_*/ ("Debug"), &Sections::Debug}};

void DrawSection(const std::string& sectionName) {
    auto it = SectionMap.find(sectionName);
    if (it != SectionMap.end()) {
        Sections::Outer();
        it->second();
    } else {
        ImGui::TextDisabled(/*xorstr_*/ ("No section matches name"));
    }
}
