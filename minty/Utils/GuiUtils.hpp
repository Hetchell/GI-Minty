#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <Windows.h>

#include "../GUI/GuiDefinitions.h"
#include "../ImGui/ImGui/imgui.h"
#include "../ImGui/ImGui/imgui_internal.h"
#include "Utils.hpp"
#include "../Config/ConfigManager.h"

void HelpMarker(const char* desc);
void AddUnderLine(ImColor col_);
void TextURL(const char* name_, const char* URL_, bool SameLineBefore_, bool SameLineAfter_);

template <typename T>
void ConfigCheckbox(const char* name, ConfigField<T>& field) {
    T& value = field.getValue();

    if (ImGui::Checkbox(name, &value)) {
        field.setValue(value);
        config::setValue(field, value);
    }
}

template <typename T>
void ConfigSliderInt(const char* name, ConfigField<T>& field, const int min, const int max) {
    T& value = field.getValue();

    if (ImGui::SliderInt(name, &value, min, max)) {
        field.setValue(value);
        //config::setValue(field, value);
    }
}

template <typename T>
void ConfigSliderFloat(const char* name, ConfigField<T>& field, const float min, const float max) {
    T& value = field.getValue();

    if (ImGui::SliderFloat(name, &value, min, max)) {
        field.setValue(value);
        //config::setValue(field, value);
    }
}
