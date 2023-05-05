#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"
#include "Sections.hpp"
#include "GuiDefinitions.h"
//#include "../Lua/luahook.hpp"
//#include "../ImGui/ImGuiNotify/imgui_notify.h"

using namespace std;

namespace gui {
    void FrameLoadGui() {

        //setlocale(LC_ALL, "C");

        ImGui::Begin("Minty");

        ImGui::BeginGroup();

        if (ImGui::Checkbox("Block key/mouse", &block_input)) // --- its automatic now, no point in this
            util::log(2, "state is: %d", block_input);

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
        ImGui::RenderNotifications();
        ImGui::PopStyleVar();

        ImGui::EndGroup();

        ImGui::End();
    }
}