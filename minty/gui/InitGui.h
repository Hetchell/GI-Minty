#pragma once

#include <Windows.h>

#include "../api/imgui/ImGui/imgui.h"
#include "../api/imgui/ImGui/imgui_impl_dx11.h"
#include "../api/imgui/ImGui/imgui_impl_win32.h"
#include "../api/imgui/ImGuiNotify/fa_solid_900.h"
#include "../api/imgui/ImGuiNotify/font_awesome_5.h"
#include "../api/imgui/ImGuiNotify/tahoma.h"
#include "../themes/fonts/FontsLoader.h"
#include "../themes/ThemeLoader.h"
#include "GuiDefinitions.h"
#include "MainGUI.h"
#include "Sections.h"
#include "../functions/Settings/Settings.h"

void MergeIconsWithLatestFont(float font_size, bool FontDataOwnedByAtlas = false);

namespace gui {
    void InitImGui(HWND window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    void Render();
}
