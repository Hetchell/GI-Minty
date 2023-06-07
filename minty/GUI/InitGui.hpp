#pragma once

#include <Windows.h>

#include "../ImGui/ImGui/imgui.h"
#include "../ImGui/ImGui/imgui_impl_dx11.h"
#include "../ImGui/ImGui/imgui_impl_win32.h"
#include "../ImGui/ImGuiNotify/fa_solid_900.h"
#include "../ImGui/ImGuiNotify/font_awesome_5.h"
#include "../ImGui/ImGuiNotify/tahoma.h"
#include "../Themes/Fonts/FontsLoader.hpp"
#include "../Themes/ThemeLoader.hpp"
#include "GuiDefinitions.h"
#include "MainGUI.h"

void MergeIconsWithLatestFont(float font_size, bool FontDataOwnedByAtlas = false);

namespace gui {
    void InitImGui(HWND window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    void Render();
}  // namespace gui