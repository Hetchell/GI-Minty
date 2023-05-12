#include "MainGUI.h"
#include "../Utils/ExtraGuiFuncs.hpp"
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

        ImGuiStyle& style = ImGui::GetStyle();
        style.Alpha = 1.0f;
        style.DisabledAlpha = 0.60f;
        style.WindowPadding = ImVec2(8, 8);
        style.WindowRounding = 4.0f;
        style.WindowBorderSize = 1.0f;
        style.WindowMinSize = ImVec2(32, 32);
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_None;
        style.ChildRounding = 5.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupRounding = 0.0f;
        style.PopupBorderSize = 1.0f;
        style.FramePadding = ImVec2(4, 3);
        style.FrameRounding = 4.0f;
        style.FrameBorderSize = 0.0f;
        style.ItemSpacing = ImVec2(8, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.CellPadding = ImVec2(4, 2);
        style.TouchExtraPadding = ImVec2(0, 0);
        style.IndentSpacing = 21.0f;
        style.ColumnsMinSpacing = 6.0f;
        style.ScrollbarSize = 14.0f;
        style.ScrollbarRounding = 9.0f;
        style.GrabMinSize = 12.0f;
        style.GrabRounding = 4.0f;
        style.LogSliderDeadzone = 4.0f;
        style.TabRounding = 4.0f;
        style.TabBorderSize = 0.0f;
        style.TabMinWidthForCloseButton = 0.0f;
        style.ColorButtonPosition = ImGuiDir_Right;
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
        style.SeparatorTextBorderSize = 3.0f;
        style.SeparatorTextAlign = ImVec2(0.0f, 0.5f);
        style.SeparatorTextPadding = ImVec2(20.0f, 3.f);
        style.DisplayWindowPadding = ImVec2(19, 19);
        style.DisplaySafeAreaPadding = ImVec2(3, 3);
        style.MouseCursorScale = 1.0f;
        style.AntiAliasedLines = true;
        style.AntiAliasedLinesUseTex = true;
        style.AntiAliasedFill = true;
        style.CurveTessellationTol = 1.25f;
        style.CircleTessellationMaxError = 0.30f;

        ImVec4* colors = ImGui::GetStyle().Colors;
        ImGui::StyleColorsLight();
        colors[ImGuiCol_CheckMark] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.10f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_Button] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.99f, 0.54f, 0.61f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.64f, 0.18f, 0.84f);
        colors[ImGuiCol_Header] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.41f, 1.00f, 0.42f, 0.61f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.29f, 0.74f, 0.31f, 0.81f);
        colors[ImGuiCol_Separator] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.84f, 0.16f, 1.00f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.41f, 0.99f, 0.43f, 0.87f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.04f, 0.58f, 0.06f, 0.88f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.42f, 0.94f, 0.43f, 0.61f);
        colors[ImGuiCol_TabActive] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.09f, 0.85f, 0.12f, 0.61f);

        ImGui::BeginChild("ChildR", ImVec2(0, 0), true, window_flags);

        DrawSection(ModuleOrder[SelectedSection]);

        ImGui::EndChild();
        ImGui::RenderNotifications();
        ImGui::PopStyleVar();

        ImGui::EndGroup();

        ImGui::End();
    }
}