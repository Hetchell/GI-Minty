#include "../MainGUI.h"
#include "../../Utils/ExtraGuiFuncs.hpp"
#include "../GuiVarDefs.h"
using namespace std;

void BeginMainTab() {
    if (ImGui::BeginTabItem("Main"))
        {
            /*if (!is_hook_success)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "WARNING! LUA NOT HOOKED");
                ImGui::Separator();
            }*/

            ImGui::SeparatorText("Player");

            static char UID_inputTextBuffer[512] = "";
            ImGui::InputTextWithHint("##input", "Enter custom UID text here...", UID_inputTextBuffer, sizeof(UID_inputTextBuffer));
            ImGui::SameLine();
            if (ImGui::Button("Update custom UID")) {
                string result = R"MY_DELIMITER(CS.UnityEngine.GameObject.Find("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"):GetComponent("Text").text = ")MY_DELIMITER" + string(UID_inputTextBuffer) + "\"";
                //luahookfunc(result.c_str());
            }
            ImGui::SameLine();
            HelpMarker("Changes your game UID to any defined text. HTML/Rich Text tags can be applied.");

            static bool show_modelswap = false;
            if (ImGui::Checkbox("Model swapper", &show_modelswap)) {
                //luahookfunc("CS.LAMLMFNDPHJ.HAFGEFPIKFK(\"snoo.\",\"snoo.\")");
            }
            ImGui::SameLine();
            HelpMarker("Swaps your avatars' models. Switch to character which model you want to set on another, press Clone; Switch to character, which model you want to replace with copied, press Paste.");
            if (show_modelswap)
            {
                ImGui::Indent();

                if (ImGui::Button("Clone model")) {
                    ////luahookfunc(char_modelswap_clone);
                }
                if (ImGui::Button("Paste model")) {
                    ////luahookfunc(char_modelswap_paste);
                }
                ImGui::Unindent();
            }

            static bool show_resizer = false;
            static float boob_size = 1.0f;
            ImGui::Checkbox("Booba resizer", &show_resizer);
            ImGui::SameLine();
            HelpMarker("Changes size of character breasts. Press Initiate and move slider.");
            if (show_resizer)
            {
                ImGui::Indent();
                if (ImGui::Button("Initiate resize")) {
                    boob_size = 1.0f;
                    ////luahookfunc(char_bub_initiate);
                }

                ImGui::SameLine();

                if (ImGui::SliderFloat("Booba scale", &boob_size, 0.0f, 4.0f, "%.3f"))
                {
                    //string result = char_bub_resize + to_string(boob_size) + "," + to_string(boob_size) + "," + to_string(boob_size) + ")";
                    ////luahookfunc(result.c_str());
                }
                ImGui::Unindent();
            }

            static bool show_avatarresizer = false;
            ImGui::Checkbox("Avatar resizer", &show_avatarresizer);
            ImGui::SameLine();
            HelpMarker("Resizes your current character's size. Just move slider. ");

            if (show_avatarresizer) {
                static float avatarsize = 1.0f;
                ImGui::Indent();
                //string result = char_avatarresize + to_string(avatarsize) + "," + to_string(avatarsize) + "," + to_string(avatarsize) + ")";

                if (ImGui::SliderFloat("Avatar scale", &avatarsize, 0.0f, 25.0f, "%.3f"))
                {
                    ////luahookfunc(result.c_str());
                }

                ImGui::SameLine();

                if (ImGui::Button("reset")) 
                {
                    //string result = string(char_avatarresize) + "1 , 1, 1)";
                    avatarsize = 1.0f;
                    ////luahookfunc(result.c_str());
                }

                ImGui::Unindent();
            }

            static bool show_colorator3000 = false;
            static float cc_r = 1.0f;
            static float cc_g = 1.0f;
            static float cc_b = 1.0f;
            static float cc_a = 1.0f;
            static ImVec4 infusion_col = ImVec4( 1.0f, 1.0f, 1.0f, 1.0f );

            ImGui::Checkbox("Infusion changer", &show_colorator3000);
            ImGui::SameLine();
            HelpMarker("Changes color of Elemental Infusion/Blade trail of your current character. Adjust color either with sliders or with color picker. Works perfectly on swords, greatswords, polearms.");
            if (show_colorator3000)
            {
                ImGui::Indent();

                if (ImGui::Button("Change")) {
                    //string result = char_eleminf + to_string(cc_r) + "," + to_string(cc_g) + "," + to_string(cc_b) + "," + to_string(cc_a) + char_eleminf_end;
                    ////luahookfunc(result.c_str());
                }
                ImGui::SameLine();

                ImGui::ColorEdit4("Infusion Color", &infusion_col.x, ImGuiColorEditFlags_AlphaBar);

                cc_r = infusion_col.x;
                cc_g = infusion_col.y;
                cc_b = infusion_col.z;
                cc_a = infusion_col.w;

                ImGui::Unindent();
            }

            static bool animcheng = false;
            static int anim_select_index = 0;
            ImGui::Checkbox("Animation Changer", &animcheng);
            ImGui::SameLine();
            HelpMarker("Change current avatar's animation.");
            if (animcheng) {
                ImGui::Indent();
                //if(ImGui::Combo("Animations", &anim_select_index, animation_options, IM_ARRAYSIZE(animation_options))) {}
        
                if (ImGui::Button("Change"))
                {
                    //string result = animchanger + string(animation_options[anim_select_index]) + animchanger2; 
                    ////luahookfunc(result.c_str());
                }
                if (ImGui::Button("Reset"))
                {
                    ////luahookfunc(animchangerreturn);
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
                //if (ImGui::Combo("Face expression", &emo_select_index, emo_options, IM_ARRAYSIZE(emo_options))) {}
                //if (ImGui::Combo("Mouth expression", &pho_select_index, pho_options, IM_ARRAYSIZE(pho_options))) {}

                if (ImGui::Button("Change"))
                {
                    //string result = emochengemo1 + string(emo_options[emo_select_index]) + emochengemo2 + string(pho_options[emo_select_index]) + emochengpho2;
                    ////luahookfunc(result.c_str());
                }

            }

            static bool isfreecam = false;
            if (ImGui::Checkbox("Free camera", &isfreecam)) {
                ////luahookfunc(cammovesffr1instantiate);
            }
            if (isfreecam) {
                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow)))
                {
                    util::log(2, "pressed right");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Translate(CS.UnityEngine.Vector3.right * CS.UnityEngine.Time.deltaTime * 10)");
                }

                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow)))
                {
                    util::log(2, "pressed left");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Translate(CS.UnityEngine.Vector3.left * CS.UnityEngine.Time.deltaTime * 10)");
                }

                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow)))
                {
                    util::log(2, "pressed up");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Translate(CS.UnityEngine.Vector3.forward * CS.UnityEngine.Time.deltaTime * 10)");
                }

                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow)))
                {
                    util::log(2, "pressed down");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Translate(CS.UnityEngine.Vector3.back * CS.UnityEngine.Time.deltaTime * 10)");
                }

                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_PageUp)))
                {
                    util::log(2, "pressed down");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Rotate(CS.UnityEngine.Vector3.up * CS.UnityEngine.Time.deltaTime * 50.0)");
                }

                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_PageDown)))
                {
                    util::log(2, "pressed down");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Rotate(-CS.UnityEngine.Vector3.up * CS.UnityEngine.Time.deltaTime * 50.0)");
                }

                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Z)))
                {
                    util::log(2, "pressed down");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Rotate(-CS.UnityEngine.Vector3.right * CS.UnityEngine.Time.deltaTime * 50.0)");
                }

                if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_X)))
                {
                    util::log(2, "pressed down");
                    ////luahookfunc("CS.UnityEngine.GameObject.Find(\"/FreeCamera\").transform:Rotate(CS.UnityEngine.Vector3.right * CS.UnityEngine.Time.deltaTime * 50.0)");
                }
            }

            ImGui::SeparatorText("World");
            static bool browser_is_enabled = false;
            if (ImGui::Checkbox("Browser", &browser_is_enabled)) {
                if (browser_is_enabled) {
                    ////luahookfunc(char_browser_on);
                }
                else {
                    ////luahookfunc(char_browser_off);
                }
            }
            ImGui::SameLine();
            HelpMarker("Spawns big interactive screen, where you can access any internet page. Click it either while holding Alt, or while charging a bow.");

            static bool no_fog = false;
            if(ImGui::Checkbox("Disable fog", &no_fog))
            {
                if (no_fog) {
                    ////luahookfunc(R"MY_DELIMITER(CS.UnityEngine.RenderSettings.fog = false)MY_DELIMITER");
                }
                else {
                    ////luahookfunc(R"MY_DELIMITER(CS.UnityEngine.RenderSettings.fog = true)MY_DELIMITER");
                }
            }
            ImGui::SameLine();
            HelpMarker("Disables visual fog in world.");

            if (ImGui::SliderFloat("Timescale", &TimeScale, 0.0f, 5.0f, "%.3f"))
            {
                //string result = "CS.UnityEngine.Time.timeScale = " + to_string(TimeScale);
                ////luahookfunc(result.c_str());
            }
            ImGui::SameLine();
            HelpMarker("Changes speed of game time. Applies to everything in game.");

            ImGui::SameLine();
            if (ImGui::Button("Reset (F11)")) {
                TimeScale = 1.0f;
                //string result = "CS.UnityEngine.Time.timeScale = 1.0";
                ////luahookfunc(result.c_str());
            }

            char inputmoFilePath[512] = "";
            char inputpngFilePath[512] = "";

            bool show_mofile_dialog = false;

            ImGui::Separator();
            ImGui::Text("MO Loader");


            ImGui::InputTextWithHint("", "Enter your path to .mo file", inputmoFilePath, sizeof(inputmoFilePath));
            ImGui::InputTextWithHint("", "Enter your path to .png file", inputpngFilePath, sizeof(inputpngFilePath));

            ImGui::SameLine();

            if (ImGui::Button("Load MO")) {
                //string result = string(char_moloader) + R"MY_DELIMITER(local moFilePath = ")MY_DELIMITER" + string(inputmoFilePath) + "\" \n" + R"MY_DELIMITER(local TextPath = ")MY_DELIMITER" + string(inputpngFilePath) + "\" \n" + string(char_moloader2);
                ////luahookfunc(result.c_str());
            }
            ImGui::SameLine();
            HelpMarker("Creates 3D object in world, which will be imported from defined paths.");


            ImGui::SeparatorText("Misc");

            /*if (ImGui::Button("123"))
            {
                //luahookfunc("a = \"booba\"");
                lua_getglobal(gi_L, "a");
                if (lua_isstring(gi_L, -1)) {
                    const char* result = lua_tostring(gi_L, -1);
                    util::log(2, "value is %s", result);
                }
                else {
                    util::log(2, "global variable 'a' is not defined");
                }
            }*/

            int first_number = 0;
            int second_number = 0;
            int third_number = 0;
            string numbers;
            static bool show_input_window = false;
            std::vector<std::pair<std::string, std::string>> dropdown_items;
            static char inputposFilePath[256] = "";

            if (ImGui::Button("Save pos"))
            {
                ////luahookfunc("pospospos = tostring(CS.MoleMole.ActorUtils.GetAvatarPos())");
                //lua_getglobal(gi_L, "pospospos");
                //if (lua_isstring(gi_L, -1)) {

                //    const char* result = lua_tostring(gi_L, -1);

                //    // Find the position of the opening and closing brackets
                //    int open_bracket_pos = string(result).find('(');
                //    int close_bracket_pos = string(result).find(')');

                //    // Extract the substring between the brackets and assign it to a new string variable
                //    string extracted_string = string(result).substr(open_bracket_pos + 1, close_bracket_pos - open_bracket_pos - 1);

                //    util::log(2, "value is %s", extracted_string);
                //    numbers = extracted_string;
                //}
                //else {
                //    util::log(2, "global variable 'pospospos' is not defined");
                //}
                //ImGui::OpenPopup("New TP position");
            }

            // Create a dropdown list
            static int selected_item = -1;
            if (ImGui::BeginCombo("Select an item", (selected_item >= 0 && selected_item < dropdown_items.size()) ? dropdown_items[selected_item].first.c_str() : "Select..."))
            {
                for (int i = 0; i < dropdown_items.size(); i++)
                {
                    bool is_selected = (selected_item == i);
                    if (ImGui::Selectable(dropdown_items[i].first.c_str(), is_selected))
                    {
                        selected_item = i;
                        //string result = "CS.MoleMole.ActorUtils.SetAvatarPos(" + to_string(std::get<0>(dropdown_items[i].second)) + "," + to_string(std::get<1>(dropdown_items[i].second)) + "," + to_string(std::get<2>(dropdown_items[i].second)) + ")";
                        string result = "CS.MoleMole.ActorUtils.SetAvatarPos(" + numbers + ")";
                        
                    }
                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            // Show a window to input a label and save the data to the dropdown when the button is pressed
            //if (show_input_window)
            //{
            //	ImGui::SetNextWindowSize(ImVec2(400, 150));
            //	ImGui::Begin("Input label", &show_input_window);
            //	ImGui::InputText("Label", &inputposFilePath, sizeof(inputposFilePath));
            //	if (ImGui::Button("Save"))
            //	{
            //		// Save the label and the three numbers to the dropdown list
            //		dropdown_items.push_back(std::make_pair(to_string(inputposFilePath), std::make_tuple(first_number, second_number, third_number)));
            //		show_input_window = false;
            //		selected_item = -1;
            //	}
            //	ImGui::End();
            //}

            if (ImGui::BeginPopup("New TP position")) {
                ImGui::InputText("Name", inputposFilePath, 256);
                if (ImGui::Button("Create")) {
                    //dropdown_items.emplace_back(string(inputposFilePath), numbers);
                    dropdown_items.push_back(std::make_pair(string(inputposFilePath), numbers));
                    memset(inputposFilePath, 0, sizeof(inputposFilePath));
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            static bool unlockfps = false;
            static float targetfps = 60;
            ImGui::Checkbox("Unlock FPS", &unlockfps);
            ImGui::SameLine();
            HelpMarker("Unlocks your framerate to defined target FPS.");
                if (unlockfps) {
                    ImGui::Indent();
                    ImGui::SliderFloat("Target FPS", &targetfps, 10.0f, 360.0f, "%.3f");
                    string result = "CS.UnityEngine.Application.targetFrameRate = " + to_string(targetfps);
                    ////luahookfunc(result.c_str());
                    ////luahookfunc("CS.UnityEngine.QualitySettings.vSyncCount = 0");
                    ImGui::Unindent();
                }

            static bool hideui = false;

            if(ImGui::Checkbox("Hide UI", &hideui)) {
                if (hideui) {
                    ////luahookfunc(char_uicamera_off);
                }
                else {
                    ////luahookfunc(char_uicamera_on);
                }
            }
            ImGui::SameLine();
            HelpMarker("Hides all game UI.");

            static bool hidenumdmg = false;

            if(ImGui::Checkbox("Hide DMG numbers", &hidenumdmg)) {
                if (hidenumdmg) {
                    ////luahookfunc(char_dmgnum_off);
                }
                else {
                    ////luahookfunc(char_dmgnum_on);
                }
            }
            ImGui::SameLine();
            HelpMarker("Hides that floating damage numbers.");

            /*static bool turnoffdithering = false;  -------- nevermind this shit wont work MHY FUCK U

            if (ImGui::Checkbox("Enable peeking", &turnoffdithering)) {
                if (turnoffdithering) {
                    //luahookfunc(enablepeeking);
                }
                else {
                    //luahookfunc(disablepeeking);
                }
            }*/

            /*static bool changefov = false; --------- SAME
            static float targetfov = 60;
            ImGui::Checkbox("Change camera FOV", &changefov);
            ImGui::SameLine();
            HelpMarker("Changes Field Of View.");
            if (changefov) {
                ImGui::Indent();
                ImGui::SliderFloat("Field Of View", &targetfov, 10.0f, 180.0f, "%.3f");
                string result = R"MY_DELIMITER(CS.UnityEngine.GameObject.Find("EntityRoot/MainCamera(Clone)"):GetComponent("Camera").main.fieldOfView = )MY_DELIMITER" + to_string(targetfov);
                //luahookfunc(result.c_str());
                ImGui::Unindent();
            }*/

            //ImGui::Separator();
            //ImGui::Text("Lua");
            ImGui::SeparatorText("Lua");
            ImGui::Checkbox("Lua editor", &showEditor);
            
            ImGui::EndTabItem();
        }
}