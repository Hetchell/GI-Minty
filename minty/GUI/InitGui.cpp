#include "InitGui.hpp"


float alpha = 0;
void MergeIconsWithLatestFont(float font_size, bool FontDataOwnedByAtlas) {
    static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};

    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = FontDataOwnedByAtlas;

    ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)fa_solid_900, sizeof(fa_solid_900), font_size, &icons_config, icons_ranges);
}

void gui::InitImGui(HWND window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
    ImGui::GetIO().ImeWindowHandle = window;

    ImFontConfig font_cfg;

    LoadFontFromResources(font_cfg, MAKEINTRESOURCEW(102), 20.f);

    font_cfg.FontDataOwnedByAtlas = false;
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

    // init notify
    MergeIconsWithLatestFont(16.f, false);

    Init();

    LoadThemes();
    LoadFonts();
}
//fade in/out anim, i was interested in this topic so i wrote this, looks good.
void gui::Render() {
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX11_NewFrame();
    ImGui::NewFrame();
    
    static double startTime = ImGui::GetTime(); // Initialize startTime when the program starts
    static bool prevShowMenu = g_ShowMenu;
    const float animDuration = 0.2f; // Adjust the animation duration as needed (shorter duration makes it faster)

    if (g_ShowMenu != prevShowMenu) {
        startTime = ImGui::GetTime(); // Reset startTime when the menu state changes
        prevShowMenu = g_ShowMenu;
    }

    float alpha = (g_ShowMenu) ? min(1.0f, (ImGui::GetTime() - startTime) / animDuration) : max(0.0f, 1.0f - (ImGui::GetTime() - startTime) / animDuration);

    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);

    if (g_ShowMenu || alpha > 0.0f) {
        gui::FrameLoadGui();
    }

    ImGui::PopStyleVar();

    Outer();

    if (ImGui::IsKeyPressed(ImGuiKey_F12, false)) {
        g_ShowMenu = !g_ShowMenu;
    }

    ImGui::Render();
}

//void gui::Render() {
//    ImGui_ImplWin32_NewFrame();
//    ImGui_ImplDX11_NewFrame();
//    ImGui::NewFrame();
//
//    if (g_ShowMenu) {
//        gui::FrameLoadGui();
//    }
//
//    Outer();
//
//    if (ImGui::IsKeyPressed(ImGuiKey_F12, false)) {
//        g_ShowMenu = !g_ShowMenu;
//    }
//
//    ImGui::Render();
//}
