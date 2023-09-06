#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <Windows.h>

#include "../GUI/GuiDefinitions.h"
#include "../ImGui/ImGui/imgui.h"
#include "../ImGui/ImGui/imgui_internal.h"
#include "Utils.hpp"

namespace ImGui {
    bool ColoredButtonV1(const char* label, const ImVec2& size, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2);
}

void HelpMarker(const char* desc);
void AddUnderLine(ImColor col_);
void TextURL(const char* name_, const char* URL_, bool SameLineBefore_, bool SameLineAfter_);
//void ShowDebugLog();

//void CreateFuncWidget(const char* label_checkbox, static bool isChecked, const char* helpText, const char* label_slider, static float f_value, static float f_valueOrigin, float min_cap, float max_cap, void (*il2FN)(int32_t));
//void CreateFuncWidget(const char* label_checkbox, static bool isChecked, static bool isSameline, const char* label_execbutton, const char* helpText, const char* label_slider, static float f_value, static float f_valueOrigin, float min_cap, float max_cap, void (*il2FN)(int32_t));
//void CreateFuncWidget(const char* label);
//void CreateFuncWidget(const char* label, static bool b_value);