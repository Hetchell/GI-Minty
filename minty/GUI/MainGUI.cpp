#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"
#include "Sections.hpp"
#include "GuiDefinitions.h"
//#include "../Themes/Fonts/fontsloader.h"
//#include "../Lua/luahook.hpp"
//#include "../ImGui/ImGuiNotify/imgui_notify.h"

using namespace std;

namespace gui {
    void FrameLoadGui() {

        //setlocale(LC_ALL, "C");

        ImGui::Begin("Minty");

        ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(0, 0), ImVec2(250, 250), ImGui::GetColorU32({255,0,0,255}), 3.0f);

        ImGui::BeginGroup();

        //ImGui::Checkbox("Block key/mouse", &block_input);
           //util::log(2, "state is: %d", block_input);

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