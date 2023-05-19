#include "MainGUI.h"
#include "../Utils/GuiUtils.hpp"
#include "Sections.hpp"
#include "GuiDefinitions.h"
//#include "../Themes/Fonts/fontsloader.h"
//#include "../Lua/luahook.hpp"
//#include "../ImGui/ImGuiNotify/imgui_notify.h"
#include "../Utils/ImageLoader/imageloader.h"

using namespace std;

namespace gui {
    void FrameLoadGui() {

        //setlocale(LC_ALL, "C");

        ImGui::Begin("Minty");

        //ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
        ////ImGui::SetNextWindowPos(ImVec2(about.width / 2, about.height * 0.063f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        //if (ImGui::Begin("Warning", nullptr, flags))
        //{
        //    auto image = ImageLoader::GetImage("IDB_PNG1");
        //    if (image)
        //        ImGui::Image(image->textureID, ImVec2(512, 512));
        //    ImGui::End();
        //}

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