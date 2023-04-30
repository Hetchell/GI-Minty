#pragma once

#include <Windows.h>

#include "../ImGui/ImGui/imgui_impl_dx11.h"
#include "../ImGui/ImGui/imgui.h"
#include "../ImGui/ImGui/imgui_impl_win32.h"
#include "MainGUI.h"
#include "MainGUI.cpp"

namespace gui {
    void InitImGui(HWND window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(pDevice, pContext);
        ImGui::GetIO().ImeWindowHandle = window;

        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        //mGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

        // Initialize notify
        //MergeIconsWithLatestFont(16.f, false);
    }

    void Render() {
        
    }
}