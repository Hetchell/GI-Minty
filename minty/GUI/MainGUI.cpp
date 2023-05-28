#include "MainGUI.h"

#include "../Utils/GuiUtils.hpp"
#include "GuiDefinitions.h"
#include "Sections.hpp"
// #include "../Themes/Fonts/fontsloader.h"
// #include "../Lua/luahook.hpp"
// #include "../ImGui/ImGuiNotify/imgui_notify.h"
#include "../Themes/themes.hpp"
#include "../Utils/ImageLoader/imageloader.h"

using namespace std;

namespace gui {
void FrameLoadGui() {
    /*----------PLACEHOLDER----------*/
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[fontindex_menu]);
    /*----------PLACEHOLDER----------*/

    // setlocale(LC_ALL, "C");

    ImGui::Begin("Minty");

    // ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
    ////ImGui::SetNextWindowPos(ImVec2(about.width / 2, about.height * 0.063f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    // if (ImGui::Begin("Warning", nullptr, flags))
    //{
    //     auto image = ImageLoader::GetImage("IDB_PNG1");
    //     if (image)
    //         ImGui::Image(image->textureID, ImVec2(512, 512));
    //     ImGui::End();
    // }

    ImGui::BeginGroup();

    // if(ImGui::Checkbox("Block key/mouse", &block_input))
    //    util::log(2, "state is: %d", block_input);

    static int SelectedSection = 0;
    if (ImGui::ListBoxHeader("##CategorySelect", ImVec2(175, -FLT_MIN))) {
        for (int i = 0; i < ModuleOrder.size(); i++) {
            bool is_selected = (i == SelectedSection);

            ImGui::PushStyleColor(ImGuiCol_Button, is_selected ? ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] : ImGui::GetStyle().Colors[ImGuiCol_Button]);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, is_selected ? ImGuiCol_ButtonActive : ImGuiCol_Button);

            if (ImGui::Button(ModuleOrder[i].c_str(), ImVec2(-1, 46))) { SelectedSection = i; }

            if (is_selected) { ImGui::SetItemDefaultFocus(); }
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


    /*----------PLACEHOLDER----------*/
    ImGui::PopFont();
    /*----------PLACEHOLDER----------*/
}
}  // namespace gui