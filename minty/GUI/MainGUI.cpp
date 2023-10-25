#include "MainGUI.h"

#include "../utils/GuiUtils.h"
#include "GuiDefinitions.h"
#include "Sections.h"
#include "../api/imgui/ImGuiNotify/imgui_notify.h"
#include "../themes/Themes.h"
//#include "../utils/image/ImageLoader.h"

using namespace std;

namespace gui {
    void FrameLoadGui() {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[fontindex_menu]);
        ImGui::Begin("Minty (CLOSE: F12)");
        ImGui::BeginGroup();

        static int SelectedSection = 0;

        if (ImGui::ListBoxHeader("##CategorySelect", ImVec2(175, -FLT_MIN))) {
            for (int i = 0; i < ModuleOrder.size(); i++) {
                bool is_selected = (i == SelectedSection);

                ImGui::PushStyleColor(ImGuiCol_Button, is_selected ? ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] : ImGui::GetStyle().Colors[ImGuiCol_Button]);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, is_selected ? ImGuiCol_ButtonActive : ImGuiCol_Button);

                if (ImGui::Button(ModuleOrder[i].c_str(), ImVec2(-1, 46)))
                    SelectedSection = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
                ImGui::PopStyleColor(2);
            }
            ImGui::ListBoxFooter();
        }

        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("ChildR", ImVec2(0, 0), true, window_flags);

        DrawSection(ModuleOrder[SelectedSection]);

        ImGui::EndChild();
        ImGui::RenderNotifications();
        ImGui::PopStyleVar();
        ImGui::EndGroup();
        ImGui::End();
        ImGui::PopFont();
    }
}
