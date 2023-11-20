#include "Themes.h"

void dark_theme() {
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_TextDisabled] = ImVec4(0.620f, 0.620f, 0.620f, 1.000f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.100f, 0.100f, 0.100f, 0.950f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.100f, 0.100f, 0.100f, 0.950f);
    colors[ImGuiCol_Border] = ImVec4(0.243f, 0.243f, 0.243f, 0.502f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.242f, 0.242f, 0.242f, 0.502f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.155f, 0.331f, 0.256f, 1.000f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.000f, 0.555f, 0.333f, 1.000f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.135f, 0.135f, 0.135f, 1.000f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.209f, 0.209f, 0.209f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.235f, 0.235f, 0.235f, 0.500f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.068f, 0.068f, 0.068f, 0.392f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.000f, 0.555f, 0.333f, 1.000f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.000f, 0.555f, 0.333f, 1.000f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.155f, 0.331f, 0.256f, 1.000f);
    colors[ImGuiCol_Button] = ImVec4(0.293f, 0.293f, 0.293f, 0.502f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.330f, 0.330f, 0.330f, 1.000f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.000f, 0.557f, 0.333f, 1.000f);
    colors[ImGuiCol_Header] = ImVec4(0.243f, 0.243f, 0.243f, 1.000f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.155f, 0.331f, 0.256f, 1.000f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.000f, 0.555f, 0.333f, 1.000f);
    colors[ImGuiCol_Separator] = ImVec4(0.243f, 0.243f, 0.243f, 0.502f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.243f, 0.243f, 0.243f, 1.000f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.155f, 0.331f, 0.256f, 1.000f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.000f, 0.555f, 0.333f, 1.000f);
    colors[ImGuiCol_Tab] = ImVec4(0.243f, 0.243f, 0.243f, 1.000f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.155f, 0.331f, 0.256f, 1.000f);
    colors[ImGuiCol_TabActive] = ImVec4(0.329f, 0.329f, 0.329f, 1.000f);
    style.FrameBorderSize = 0.0f;
}

void light_theme() {
    ImGui::StyleColorsLight();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.144f, 0.144f, 0.144f, 1.000f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.532f, 0.532f, 0.532f, 1.000f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.875f, 0.875f, 0.875f, 0.950f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.872f, 0.872f, 0.872f, 0.950f);
    colors[ImGuiCol_Border] = ImVec4(0.980f, 0.980f, 0.980f, 0.502f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.982f, 0.982f, 0.982f, 0.502f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.886f, 1.000f, 0.951f, 1.000f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.382f, 0.852f, 0.653f, 1.000f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.890f, 0.890f, 0.890f, 1.000f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.000f, 1.000f, 1.000f, 0.500f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.382f, 0.852f, 0.653f, 1.000f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.382f, 0.852f, 0.653f, 1.000f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.886f, 1.000f, 0.951f, 1.000f);
    colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.502f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.382f, 0.852f, 0.653f, 1.000f);
    colors[ImGuiCol_Header] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.886f, 1.000f, 0.951f, 1.000f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.382f, 0.852f, 0.653f, 1.000f);
    colors[ImGuiCol_Separator] = ImVec4(0.980f, 0.980f, 0.980f, 0.502f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.886f, 1.000f, 0.951f, 1.000f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.382f, 0.852f, 0.653f, 1.000f);
    colors[ImGuiCol_Tab] = ImVec4(0.927f, 0.927f, 0.927f, 1.000f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.886f, 1.000f, 0.951f, 1.000f);
    colors[ImGuiCol_TabActive] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    style.FrameBorderSize = 0.0f;
}

// i will update this theme later
/*void red_theme() {
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.750f, 0.750f, 0.750f, 1.000f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.450f, 0.450f, 0.450f, 1.000f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.075f, 0.075f, 0.075f, 0.950f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.075f, 0.075f, 0.075f, 0.950f);
    colors[ImGuiCol_Border] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.209f, 0.209f, 0.209f, 1.000f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.479f, 0.091f, 0.181f, 1.000f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.135f, 0.135f, 0.135f, 1.000f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.209f, 0.209f, 0.209f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.722f, 0.132f, 0.132f, 0.500f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.048f, 0.048f, 0.048f, 0.392f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.479f, 0.091f, 0.181f, 1.000f);
    colors[ImGuiCol_Button] = ImVec4(0.209f, 0.209f, 0.209f, 1.000f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.479f, 0.091f, 0.181f, 1.000f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    colors[ImGuiCol_Header] = ImVec4(0.209f, 0.209f, 0.209f, 1.000f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.479f, 0.091f, 0.181f, 1.000f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    colors[ImGuiCol_Separator] = ImVec4(0.243f, 0.243f, 0.243f, 0.502f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.209f, 0.209f, 0.209f, 1.000f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.479f, 0.091f, 0.181f, 1.000f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    colors[ImGuiCol_Tab] = ImVec4(0.209f, 0.209f, 0.209f, 1.000f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.479f, 0.091f, 0.181f, 1.000f);
    colors[ImGuiCol_TabActive] = ImVec4(0.722f, 0.132f, 0.132f, 1.000f);
    style.FrameBorderSize = 0.0f;
}*/

void cozy_style() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.60f;
    style.WindowPadding = ImVec2(10, 10);
    style.WindowRounding = 8.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32, 32);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding = 5.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(6, 6);
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(10, 6);
    style.ItemInnerSpacing = ImVec2(8, 8);
    style.CellPadding = ImVec2(4, 2);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 30.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 20.0f;
    style.ScrollbarRounding = 2.0f;
    style.GrabMinSize = 15.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 3.0f;
    style.LogSliderDeadzone = 4.0f;
    style.TabRounding = 4.0f;
    style.TabBorderSize = 1.0f;
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
}

void cozy_square_style() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.PopupRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.TabRounding = 0.0f;
}

void setTheme(int themeIndex) {
    switch (themeIndex) {
    case 1:
        dark_theme();
        theme_index = 1;
        break;
    case 2:
        light_theme();
        theme_index = 2;
        break;
    /*case 3:
        red_theme();
        theme_index = 3;
        break;*/
    default:
        break;
    }

    config::setValue("general:theme", "color", themeIndex);
}

void setStyle(int styleIndex) {
    switch (styleIndex) {
        case 1:
            style_index = 1;
            cozy_style();
            break;
        case 2:
            style_index = 2;
            cozy_square_style();
            break;
        default:
            break;
    }

    config::setValue("general:theme", "style", styleIndex);
}

void setFont(int fontIndex) {
    switch (fontIndex) {
        case 1:
            fontindex_menu = 1;
            break;
        case 2:
            fontindex_menu = 0;
            break;
        // case 3:
        //     fontindex_menu = 2;
        //     break;
        default:
            break;
    }

    config::setValue("general:theme", "font", fontIndex);
}
