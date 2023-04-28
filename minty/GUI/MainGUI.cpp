#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"
#include "Sections.hpp"
#include "../IL2CPP/Functions/molemole.h"

using namespace std;

namespace gui {
    void FrameLoadGui() {

        setlocale(LC_ALL, "C");

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
            ImGui::BeginGroup();
            static bool block_key = false;

            if (ImGui::Checkbox("Block key/mouse", &block_key)) {
                //renderer::SetInputLock(this, m_IsBlockingInput);
            }

            static int SelectedSection = 0;

            if (ImGui::ListBoxHeader("##CategorySelect", ImVec2(175, -FLT_MIN))) {
                for (int i = 0; i < ModuleOrder.size(); i++) {
                    bool is_selected = (i == SelectedSection);
                    if (ImGui::Selectable(ModuleOrder[i].c_str(), is_selected)) {
                        SelectedSection = i;
                    }
                }
                ImGui::ListBoxFooter();
                ImGui::SetItemDefaultFocus();
            }

            ImGui::EndGroup();

            ImGui::SameLine();

            ImGui::BeginGroup();

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("ChildR", ImVec2(0, 0), true, window_flags);

            DrawSection(ModuleOrder[SelectedSection]);

            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::EndTabItem();
            ImGui::EndGroup();
            ImGui::EndTabBar();

            ImGui::End();

        }
    }
}