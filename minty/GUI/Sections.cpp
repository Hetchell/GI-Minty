#include <string>
#include <unordered_map>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../ImGui/ImGui/imgui.h"

#include "../Games/games.h"

#include "../IL2CPP/Functions/bootyfixer.h"
#include "../IL2CPP/Functions/dialogskip.h"
#include "../IL2CPP/Functions/dumbenemies.h"
#include "../IL2CPP/Functions/godmode.h"
#include "../IL2CPP/Functions/infinityenergy.h"
#include "../IL2CPP/Functions/infinitystamina.h"
#include "../IL2CPP/Functions/nocd.h"
#include "../IL2CPP/Functions/noclip.h"
#include "../IL2CPP/Functions/uimisc.h"
#include "../IL2CPP/Functions/unlockfps.h"
#include "../IL2CPP/Functions/multihit.h"

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

bool show_rpc = true;
ImGuiID textureID = 0;

extern bool is_lua_hooked;

extern uintptr_t baseAddress;
extern uintptr_t unityPlayerAddress;


std::vector<std::string> lua_list;
std::string last_lua_string;

static bool ifshowfps;

static bool ifnoclip, ifaltSpeed = false;
static float fNoClip = 10.f;
static float faltNoClip = 25.f;

std::vector<std::string> ModuleOrder = {
    "Player",
    "World",
    "Misc",
    "Lua",
    "Minigames",
    //"Themes",
    //"Debug",
    "About",
    "Settings"
};

namespace Sections {

    void Player() {
        ImGui::SeparatorText("Avatar");

        il2fns::Infinity_Stamina();

        il2fns::GodMode();

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
        ImGui::Checkbox("Chest resizer", &show_resizer);
        ImGui::SameLine();
        HelpMarker("Changes size of character chest. Press Initiate and adjust slider.");
        if (show_resizer) {
            ImGui::Indent();
            if (ImGui::Button("Initiate resize")) {
                boob_size = 1.0f;
                last_lua_string = char_bub_initiate;
            }

            ImGui::SameLine();

            if (ImGui::SliderFloat("Chest size", &boob_size, 0.0f, 4.0f, "%.3f")) {
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
            if (ImGui::Combo("Face expression", &emo_select_index, emo_options, IM_ARRAYSIZE(emo_options))) {}
            if (ImGui::Combo("Mouth expression", &pho_select_index, pho_options, IM_ARRAYSIZE(pho_options))) {}

            if (ImGui::Button("Change")) {
                std::string result = emochengemo1 + std::string(emo_options[emo_select_index]) + emochengemo2 + std::string(pho_options[emo_select_index]) + emochengpho2;
                last_lua_string = result;
            }
            ImGui::Unindent();
        }

        static bool show_avatarresizer = false;
        static float avatarsize = 1.0f;
        ImGui::Checkbox("Avatar resizer", &show_avatarresizer);
        ImGui::SameLine();
        HelpMarker("Resizes your current character.");

        if (show_avatarresizer) {
            ImGui::Indent();
            std::string result = char_avatarresize + std::to_string(avatarsize) + "," + std::to_string(avatarsize) + "," + std::to_string(avatarsize) + ")";

            if (ImGui::SliderFloat("Avatar scale", &avatarsize, 0.0f, 25.0f, "%.3f")) {
                last_lua_string = result;
            }

            ImGui::SameLine();

            if (ImGui::Button("Reset")) {
                std::string result = std::string(char_avatarresize) + "1 , 1, 1)";
                avatarsize = 1.0f;
                last_lua_string = result;
            }

            ImGui::Unindent();
        }
        else {
            std::string result = std::string(char_avatarresize) + "1 , 1, 1)";
            avatarsize = 1.0f;
            //last_lua_string = result;
        }

        static bool ignoreCol = true;
        static int iNoClip;

        if (ImGui::Checkbox("Noclip", &ifnoclip)) il2fns::NoClipInit(ifnoclip);

        if (ifnoclip) {
            //il2fns::OnNoclip();

            ImGui::Indent();

            if (ImGui::SliderFloat("##NoClip speed", &fNoClip, 1.f, 30.f, "%.1f")) il2fns::NoClipSpeed(fNoClip);
            ImGui::Checkbox("Alt speed", &ifaltSpeed);

            if (ifaltSpeed) {
                ImGui::Indent();

                ImGui::SliderFloat("##NoClip alt speed", &faltNoClip, 1.f, 50.f, "%.1f");

                //if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl, true))
                //    il2fns::NoClipSpeed(faltNoClip);

                //if (ImGui::IsKeyReleased(ImGuiKey_LeftCtrl))
                //    il2fns::NoClipSpeed(fNoClip);

                ImGui::Unindent();
            }

            if (ImGui::Checkbox("Ignore Collisions", &ignoreCol)) {
                if (ignoreCol) {
                    il2fns::colmod(0);
                }
                else {
                    il2fns::colmod(1);
                }
            }

            if (ignoreCol) {

            }


            ImGui::Unindent();
        }

        ImGui::SeparatorText("Skills");

        il2fns::Infinity__Energy();

        il2fns::LCAvatarCombat_NoCD();

        il2fns::NoBowCD();

        //static bool ifnoclip = false;
        //if (ImGui::Checkbox("Noclip", &ifnoclip)) {
        //    saveFuncStateToJson("Noclip", ifnoclip);
        //    il2fns::OnNoclip(ifnoclip);
        //}

        il2fns::MultiHit();
    }

    static float TimeScale = 1.0f;
    void World() {
        static bool timescale = false;
        if (ImGui::Checkbox("Change time speed", &timescale)) {
            if (!timescale)
                app::UnityEngine__set__Timescale(1);
        }
        ImGui::SameLine();

        HelpMarker("Changes the speed at which the game runs.");

        if (timescale) {
            ImGui::Indent();
            if (ImGui::SliderFloat("Timescale", &TimeScale, 0.0f, 5.0f, "%.3f")) {
                app::UnityEngine__set__Timescale(TimeScale);
            }

            ImGui::SameLine();
            HelpMarker("Changes speed of game time. Applies to everything in game.");

            ImGui::Unindent();
        }

        il2fns::DumbEnemies();
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

        ImGui::Text("Minty version 1.32");
        ImGui::Text("ImGui version: %s", ImGui::GetVersion());
        ImGui::Text("Design made with love by KittyKate :3");

        ImGui::SeparatorText("Contributors");

        ImGui::TextColored(ImVec4(235.0 / 255.0, 64.0 / 255.0, 52.0 / 255.0, 1.0), "Owner: MintyGingy");
        ImGui::TextColored(ImVec4(219.0 / 255.0, 57.0 / 255.0, 219.0 / 255.0, 1.0), "Co-founder: Moistcrafter");
        ImGui::TextColored(ImVec4(57.0 / 255.0, 68.0 / 255.0, 219.0 / 255.0, 1.0), "Contributors: EtoShinya, KittyKate, lilmayofuksu, USSY, akioukun, m3gan");
        ImGui::TextColored(ImVec4(255, 0, 212, 255), "Donaters: EtoShinya <3 <3, Thomas_Heath, Blair, unmeinoshonen, USSY");
        ImGui::TextColored(ImVec4(0, 255, 179, 255), "Special thanks to family: Futchev, yarik0chka, keitaro_gg");

        ImGui::Text("Minty Github: ");
        TextURL("Link", "https://github.com/kindawindytoday/Minty-Releases", true, false);

        ImGui::Text("KWT Discord: ");
        TextURL("Link", "https://discord.gg/kindawindytoday", true, false);
    }

    void Themes() {
        ImGui::SeparatorText("Theme");
        /*----------PLACEHOLDER----------*/
        static int themeIndex = 1;

        nlohmann::json cfgjsonobj;
        std::ifstream config_file("minty");
        nlohmann::json config_json;
        config_file >> config_json;
        config_file.close();

        if (ImGui::RadioButton("Dark", &themeIndex, 1)) {
            settheme(1);
            cfgjsonobj["theme"]["color"] = 1;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        if (ImGui::RadioButton("Light", &themeIndex, 2)) {
            settheme(2);
            cfgjsonobj["theme"]["color"] = 2;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        /*if (ImGui::RadioButton("Red", &themeIndex, 3)) {
            settheme(3);
            cfgjsonobj["theme"]["color"] = 3;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }*/

        ImGui::SeparatorText("Style");

        static int themestyleindex = 1;

        if (ImGui::RadioButton("Cozy", &themestyleindex, 1)) {
            setstyle(1);
            cfgjsonobj["theme"]["style"] = 1;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        if (ImGui::RadioButton("Cozy Squared", &themestyleindex, 2)) {
            setstyle(2);
            cfgjsonobj["theme"]["style"] = 2;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        ImGui::SeparatorText("Font");

        static int fontSelectionIndex = 0;
        if (ImGui::RadioButton("Normal", &fontSelectionIndex, 0)) {
            setfont(1);
        }

        if (ImGui::RadioButton("Bold", &fontSelectionIndex, 1)) {
            setfont(2);
        }

        ImGui::SeparatorText("Customize");
        //ImGui::TextDisabled("DEBUG");
        ImGui::Checkbox("Show Style Editor", &show_style_editor);
        /*----------PLACEHOLDER----------*/
    }
    void Settings() {
        std::ifstream config_file("minty");
        nlohmann::json config_json;
        config_file >> config_json;
        config_file.close();

        static int initinitde = config_json["general"]["initDelay"];
        show_rpc = config_json["general"]["showRPC"];

        ImGui::SeparatorText("General");

        ImGui::Checkbox("Show ImGui's cursor", &ImGui::GetIO().MouseDrawCursor);

        if (ImGui::Checkbox("Show current FPS", &ifshowfps)) {
            nlohmann::json cfgjsonobj;
            std::ifstream config_file("minty");
            nlohmann::json config_json;
            config_file >> config_json;
            config_file.close();
            cfgjsonobj["general"]["ShowFPS"] = ifshowfps;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        ImGui::Checkbox("Block input", &block_input);

        if (ImGui::Checkbox("Show Discord RPC", &show_rpc)) {
            nlohmann::json cfgjsonobj;
            std::ifstream config_file("minty");
            nlohmann::json config_json;
            config_file >> config_json;
            config_file.close();
            cfgjsonobj["general"]["showRPC"] = show_rpc;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }
        ImGui::SameLine(); HelpMarker("Turn Discord custom RPC on/off. Requires re-entering game.");

        if (ImGui::SliderInt("Initialization delay (ms)", &initinitde, 0, 60000)) {
            nlohmann::json cfgjsonobj;
            std::ifstream config_file("minty");
            nlohmann::json config_json;
            config_file >> config_json;
            config_file.close();
            cfgjsonobj["general"]["initDelay"] = initinitde;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }
        ImGui::SameLine(); HelpMarker("Change delay before showing menu. May cause lags while opening, so try to change this value in case.");

        //ImGui::SeparatorText("Hotkeys");

        //std::map<int, std::function<void()>> hotkeyCallbacks;
        //std::map<int, ImGuiKey> intToImGuiKeyMap;
        //int selectedHotkey = -1;
        //char hotkeyText[32] = "Press key...";
        //ImGui::InputText("Hotkey", hotkeyText, sizeof(hotkeyText), ImGuiInputTextFlags_ReadOnly);

        //if (ImGui::IsItemClicked())
        //{
        //    strcpy(hotkeyText, "Press key...");
        //}

        //if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
        //{
        //    strcpy(hotkeyText, "None");
        //}
        //else
        //{
        //    for (const auto& [intValue, key] : intToImGuiKeyMap)
        //    {
        //        if (ImGui::IsKeyPressed(key) && key != ImGuiKey_Tab)
        //        {
        //            const char* keyName = ImGui::GetKeyName(key);
        //            util::log(M_Info, "keyname: %s", keyName);
        //            strcpy(hotkeyText, keyName);

        //            auto callback = hotkeyCallbacks.find(intValue);
        //            if (callback != hotkeyCallbacks.end())
        //            {
        //                callback->second();  // Call the associated callback function
        //            }
        //        }
        //    }
        //}

        ImGui::SeparatorText("Theme");
        /*----------PLACEHOLDER----------*/
        static int themeIndex = 1;

        nlohmann::json cfgjsonobj;
        std::ifstream config_file111("minty");
        nlohmann::json config_json111;
        config_file111 >> config_json111;
        config_file111.close();

        if (ImGui::RadioButton("Dark", &themeIndex, 1)) {
            settheme(1);
            cfgjsonobj["theme"]["color"] = 1;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        if (ImGui::RadioButton("Light", &themeIndex, 2)) {
            settheme(2);
            cfgjsonobj["theme"]["color"] = 2;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        /*if (ImGui::RadioButton("Red", &themeIndex, 3)) {
            settheme(3);
            cfgjsonobj["theme"]["color"] = 3;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }*/

        ImGui::SeparatorText("Style");

        static int themestyleindex = 1;

        if (ImGui::RadioButton("Cozy", &themestyleindex, 1)) {
            setstyle(1);
            cfgjsonobj["theme"]["style"] = 1;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        if (ImGui::RadioButton("Cozy Squared", &themestyleindex, 2)) {
            setstyle(2);
            cfgjsonobj["theme"]["style"] = 2;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }

        ImGui::SeparatorText("Font");

        static int fontSelectionIndex = 0;
        if (ImGui::RadioButton("Normal", &fontSelectionIndex, 0)) {
            setfont(1);
        }

        if (ImGui::RadioButton("Bold", &fontSelectionIndex, 1)) {
            setfont(2);
        }

        ImGui::SeparatorText("Customize");
        //ImGui::TextDisabled("DEBUG");
        ImGui::Checkbox("Show Style Editor", &show_style_editor);
    }

    void Debug() {
        ImGui::SeparatorText("Debug");

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("Dear ImGui version: %s", ImGui::GetVersion());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        ImGui::SeparatorText("Status");

        const char* hook_state_name[] = { "not hooked", "hooked" };
        ImVec4 hooked_name_color[] = { ImVec4(0.76078f, 0.219607f, 0.219607f, 1), ImVec4(0.12156f, 0.8f, 0.2f, 1.0f) };

        // ImGui::Text("il2cpp: ");
        // ImGui::SameLine();
        // ImGui::TextColored(hooked_name_color[static_cast<int>(is_il2cpp_hooked)], hook_state_name[static_cast<int>(is_il2cpp_hooked)]);
        // ImGui::Text("Lua: ");
        // ImGui::SameLine();
        // ImGui::TextColored(hooked_name_color[static_cast<int>(is_lua_hooked)], hook_state_name[static_cast<int>(is_lua_hooked)]);

        /*----------TEMP----------*/

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
        ImGui::SeparatorText("Interface");

        il2fns::UnlockFps();

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
            }
            else {
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

        il2fns::BootyFixer();

        il2fns::DialogSkip();

        il2fns::CutsceneSkip();

        il2fns::ChestIndicator();

        il2fns::SkipAnim();

        ImGui::SeparatorText("Camera");

        il2fns::SetFov();

        //static bool ifElem = false;
        //if (ImGui::Checkbox("Infinity Elemental sight", &ifElem)) {
        //    saveFuncStateToJson("ElemSight", ifElem);
        //    il2fns::ElemSight(ifElem);
        //} ImGui::SameLine(); HelpMarker("Infinite duration for Elemental Sight.");

        /* static bool ifOTI = false;
        if (ImGui::Checkbox("Open team immediately", &ifOTI)) {
            il2fns::OpenTeamImm(ifOTI);
        }*/

        // il2fns::CameraZoom(); ебаные китайцы вы нахуя поля опять перемешали мне че делать с ними пожалуйста засуньте их себе в жопу спасибо за понимание :kissing_heart:

    }

    void Lua() {
        ImGui::SeparatorText("Editor");
        ImGui::Checkbox("Show Lua editor", &show_lua_editor);
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
                        }
                        catch (...) {
                            util::log(M_Error, "lua excep");
                        }
                        /*if (last_ret_code == 0) {
                            util::log(M_Info, "compilation success: %s", last_tolstr);
                        }*/
                    }
                    else {
                        ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Lua is not hooked." });
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

}// namespace Sections

void UltraOuter() {
    std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    ifshowfps = config_json["general"]["ShowFPS"];
    if (ifshowfps) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("##FPS", NULL, flags);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }

    if (ifnoclip) {
        il2fns::OnNoclip();

        if (ifaltSpeed) {
            if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl, true))
                il2fns::NoClipSpeed(faltNoClip);

            if (ImGui::IsKeyReleased(ImGuiKey_LeftCtrl))
                il2fns::NoClipSpeed(fNoClip);
        }
    }
}

using DrawFunction = void (*)();

const std::unordered_map<std::string, DrawFunction> SectionMap = {
    {"Player", &Sections::Player},
    {"World", &Sections::World},
    {"Misc", &Sections::Misc},
    {"Lua", &Sections::Lua},
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
