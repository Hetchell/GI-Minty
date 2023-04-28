#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"
#include "../IL2CPP/Functions/molemole.h"

using namespace std;

namespace gui {
    void FrameLoadGui() {
        ImGui::GetStyle().IndentSpacing = 16.0f;

        //ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[fontindex_menu]);

        setlocale(LC_ALL, "C");

        static bool showEditor = false;
        static bool isopened = true;
        static bool show_compile_log = false;

        static char* file_dialog_buffer = nullptr;
        static char path3[500] = "";

        static float TimeScale = 1.0f;
        static bool themeInit = false;

  
        // if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_F11)))
        // {
        //     TimeScale = 1.0f;
        //     string result = "CS.UnityEngine.Time.timeScale = 1.0";
        //     //luahookfunc(result.c_str());
        // }

            ImGui::Begin("Minty");
            ImGui::BeginTabBar("Minty");

            if (ImGui::BeginTabItem("Main"))
            {
                /*if (!is_hook_success)
                {
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "WARNING! LUA NOT HOOKED");
                    ImGui::Separator();
                }*/
                if (ImGui::Button("PLEASE WORK")) {
                    il2fns::MoleMole__ActorUtils__ShowMessage_I();
                }

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

            if (showEditor)
            {
                /*if (FileDialog::file_dialog_open) {
                    FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, file_dialog_buffer, sizeof(file_dialog_buffer), FileDialog::file_dialog_open_type);
                }*/

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
                ImGui::Begin("Lua editor", &showEditor, ImGuiWindowFlags_MenuBar);

                if (ImGui::Button("Run"))
                {
                    string code = editor.GetText();
                    if (!code.empty() && code.find_first_not_of(" \t\n\v\f\r") != string::npos)
                    {
                        /*if (is_hook_success) {
                            //luahookfunc(code.c_str());
                            if (last_ret_code == 0) {
                                util::log(2,"compilation success: %s", last_tolstr);
                            }
                        }
                        else {
                            util::log(0, "Lua is not hooked", "");
                        }*/
                    }
                }
                ImGui::SameLine();
                //saver to button below.

                static vector<pair<string, function<void()>>> buttonFuncs;
                static char buttonLabel[256] = "";

                if (ImGui::Button("Create new button")) {
                    ImGui::OpenPopup("New button");
                }
                ImGui::SameLine();
                ImGui::Checkbox("Show log", &show_compile_log);

                if (ImGui::BeginPopup("New button")) {
                    ImGui::InputText("Label", buttonLabel, 256);
                    if (ImGui::Button("Create")) {
                        string functionText = editor.GetText();
                        function<void()> buttonFunc = [functionText]() {
                            ////luahookfunc(functionText.c_str());
                        };
                        buttonFuncs.emplace_back(string(buttonLabel), buttonFunc);
                        memset(buttonLabel, 0, sizeof(buttonLabel));
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }

                ImGui::Begin("Minty");
                for (const auto& button : buttonFuncs) {
                    if (ImGui::Button(button.first.c_str())) {
                        button.second();
                    }
                }
                ImGui::End();

                if (ImGui::BeginMenuBar())
                {
                    //ImGui::InputText("##path3", path3, sizeof(path3));
                    if (ImGui::BeginMenu("File"))
                    {
                        if (ImGui::MenuItem("Load .lua file"))
                        {
                            //file_dialog_buffer = path3;
                            //FileDialog::file_dialog_open = true;
                            //FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
                            //FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, file_dialog_buffer, sizeof(file_dialog_buffer), FileDialog::file_dialog_open_type);
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

                ImGui::End();
            }
            
            ImGuiTextFilter Filter;
            if (show_compile_log)
            {
                ImGui::Begin("Log", &show_compile_log);
                if (ImGui::SmallButton("[Debug] Add 5 entries"))
                {
                    static int counter = 0;
                    const char* categories[3] = { "Info", "Warning", "Error" };
                    const char* words[] = { "virus", "sob", "leak", "plead", "windsensinden", "windy", "ril", "fek" };
                    for (int n = 0; n < 5; n++)
                    {
                        const char* category = categories[counter % IM_ARRAYSIZE(categories)];
                        const char* word = words[counter % IM_ARRAYSIZE(words)];
                        log_textbuf.appendf("[Minty:%s] [%05d] Hello, current time is %.1f, here's a word: '%s'\n", category, ImGui::GetFrameCount(), ImGui::GetTime(), word);
                        counter++;
                    }
                }
                ImGui::SameLine();
                if (ImGui::SmallButton("Clear")) {
                    log_textbuf.clear();
                }
                ImGui::SameLine();
                if (ImGui::SmallButton("Copy")) {
                    ImGui::SetClipboardText(log_textbuf.begin());
                }
                Filter.Draw("Filter");
                ImGui::Separator();
                ImGui::BeginChild("LogScroll", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

                if (Filter.IsActive())
                {
                    const char* buf_begin = log_textbuf.begin();
                    const char* buf_end = log_textbuf.end();
                    ImGuiTextBuffer log_filtered;
                    while (buf_begin < buf_end)
                    {
                        const char* line_end = strchr(buf_begin, '\n');
                        if (Filter.PassFilter(buf_begin, line_end))
                        {
                            log_filtered.append(buf_begin, line_end);
                            log_filtered.append("\n");
                        }
                        buf_begin = line_end + 1;
                    }
                    ImGui::TextUnformatted(log_filtered.begin(), log_filtered.end());
                }
                else
                {
                    ImGui::TextUnformatted(log_textbuf.begin(), log_textbuf.end());
                }

                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                {
                    ImGui::SetScrollHereY(1.0f);
                }
                ImGui::EndChild();	
                ImGui::End();
            }
            static bool show_style_editor = false;
            if (ImGui::BeginTabItem("Themes"))
            {
                // Content for themes
                ImGui::Text("Theme colors");

                static int themeIndex = 0;

                if (ImGui::RadioButton("Default dark", &themeIndex, 0))
                {
                    settheme(1);
                }

                if (ImGui::RadioButton("Default light", &themeIndex, 1))
                {
                    settheme(2);
                }

                if (ImGui::RadioButton("Default classic", &themeIndex, 2))
                {
                    settheme(3);
                }

                if (ImGui::RadioButton("Dark theme", &themeIndex, 3))
                {
                    settheme(4);
                }

                if (ImGui::RadioButton("Minty Red", &themeIndex, 4))
                {
                    settheme(5);
                }
                
                if (ImGui::RadioButton("Minty Mint", &themeIndex, 5))
                {
                    settheme(6);
                }

                if (ImGui::RadioButton("Minty Mint Light", &themeIndex, 6))
                {
                    settheme(7);
                }

                ImGui::Separator();
                ImGui::Text("Theme style");

                static int themestyleindex = 0;

                if (ImGui::RadioButton("Rounded compact style", &themestyleindex, 0))
                {
                    setstyle(1);
                }
                
                if (ImGui::RadioButton("Big", &themestyleindex, 1))
                {
                    setstyle(2);
                }

                if (ImGui::RadioButton("ImGui Default", &themestyleindex, 2))
                {
                    setstyle(3);
                }

                if (ImGui::RadioButton("Big Squared", &themestyleindex, 3))
                {
                    setstyle(4);
                }

                ImGui::Separator();

                ImGui::Text("Menu font");

                static int fontSelectionIndex = 0;
                if (ImGui::RadioButton("Jetbrains Mono", &fontSelectionIndex, 0))
                {
                    setfont(1);
                }

                if (ImGui::RadioButton("Myriad Pro", &fontSelectionIndex, 1))
                {
                    setfont(2);
                }

                ImGui::Separator();

                ImGui::Text("Style Editor");

                ImGui::Checkbox("Show Style Editor", &show_style_editor);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("About"))
            {
                // Content for About
                ImGui::Text("Minty BETA v0.7.1 WIP");
                ImGui::Text("ImGui version: %s", ImGui::GetVersion());

                ImVec4 linkColor = ImVec4(34.0f/255.0f, 132.0f/255.0f, 230.0f/255.0f, 1.0f);

                ImGui::Text("Contributors: мятный пряник#0086, Moistcrafter#9172, yarik#4571, azzu#2731");
                ImGui::Separator();

                ImGui::TextColored(linkColor, "KWT Team Discord (click)");
                if (ImGui::IsItemClicked()) {
                    system("start https://discord.gg/kj7PQrr6CV");
                }
                ImGui::TextColored(linkColor, "KWT Team GitHub (click)");
                if (ImGui::IsItemClicked()) {
                    system("start https://github.com/kindawindytoday");
                }
                ImGui::Separator();

                ImGui::EndTabItem();
            }

            static bool show_debug_metrics = false;
            
            if (ImGui::BeginTabItem("Debug"))
            {
                ImGui::Checkbox("Show Debug Metrics", &show_debug_metrics);
                ImGui::EndTabItem();
            }

            if(show_debug_metrics)
            ImGui::ShowMetricsWindow(&show_debug_metrics);
            if (show_style_editor)
            {
                ImGui::Begin("ImGui Style Editor", &show_style_editor);
                ImGui::ShowStyleEditor();
                ImGui::End();
            }
            
            static char Dump_Path[1024] = "";

            if (ImGui::BeginTabItem("Dumping"))
            {

                ImGui::InputTextWithHint("Dump output path", "C:/Users/User/Desktop", Dump_Path, sizeof(Dump_Path));
                ImGui::SameLine();
                HelpMarker("Provide a valid path to dump. \nProvide an existing folder as it cannot create new folders.");

                ImGui::Separator();

                if (ImGui::Button("Dump CSharp")) {
                    if(strlen(Dump_Path) != 0)
                    {
                        //string result = "local DUMP_FOLDER = \"" + string(Dump_Path) + "\"" + char_dumpcs_part1 + char_dumpcs_part2;
                        ////luahookfunc(result.c_str());
                    }
                }
                if(ImGui::IsItemHovered() && strlen(Dump_Path) != 0){
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "WARNING! This will freeze your game, give it 20 minutes or so to complete.");
                }
                else{}
                
                if(ImGui::Button("Dump current hierarchy"))
                {
                    if(strlen(Dump_Path) != 0)
                    {
                        //string result = "local dump_path = \"" + string(Dump_Path) + "\"" + char_dump_hierarchy;
                        ////luahookfunc(result.c_str());
                    }
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Games"))
            {
                ImGui::SeparatorText("Lights out");
                //lightsout_main();

                ImGui::SeparatorText("Tic Tac Toe");
                    
                //tictactoe_main();

                ImGui::SeparatorText("");

                //wordle_main();
                    
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
            ImGui::End();
        
        //ImGui::PopFont();
    }
}