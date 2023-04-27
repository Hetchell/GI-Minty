#pragma once
#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"
#include "GuiVarDefs.h"
#include "Tabs/Tabs.h"

using namespace std;

namespace gui {
    void FrameLoadGui() {
        //ImGui::GetStyle().IndentSpacing = 16.0f;

        //ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[fontindex_menu]);

        setlocale(LC_ALL, "C");
        
        
        // if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_F11)))
        // {
        //     TimeScale = 1.0f;
        //     string result = "CS.UnityEngine.Time.timeScale = 1.0";
        //     //luahookfunc(result.c_str());
        // }

            ImGui::Begin("Minty");
            ImGui::BeginTabBar("Minty");

           
            BeginMainTab();
            
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
            BeginThemesTab();

            BeginAboutTab();

            BeginDebugTab();

            if(show_debug_metrics)
                ImGui::ShowMetricsWindow(&show_debug_metrics);

            if (show_style_editor) {
                ImGui::Begin("ImGui Style Editor", &show_style_editor);
                ImGui::ShowStyleEditor();
                ImGui::End();
            }
            
            /*static char Dump_Path[1024] = "";

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
            }*/

            BeginGamesTab();

            ImGui::EndTabBar();
            ImGui::End();
        
        //ImGui::PopFont();
    }
}