#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <Windows.h>

#include "../GUI/GuiDefinitions.h"
#include "../ImGui/ImGui/imgui.h"
#include "../ImGui/ImGui/imgui_internal.h"
#include "../ImGui/ImGui/imgui_stdlib.h"
#include "Utils.hpp"
#include "../Config/ConfigManager.h"
#include "Logger.h"

void HelpMarker(const char* desc);

#define END_WIDGET() \
    if (description != nullptr) { \
        ImGui::SameLine(); \
        HelpMarker(description); \
    }

template <typename T>
void ConfigCheckbox(const char* name, ConfigField<T>& field, const char* description = nullptr) {
    T& value = field.getValue();

    if (ImGui::Checkbox(name, &value)) {
        field.setValue(value);
        config::setValue(field, value);
    }
    END_WIDGET();
}

template <typename T>
void ConfigInputText(const char* name, ConfigField<T>& field, const char* description = nullptr) {
    T& value = field.getValue();

    if (ImGui::InputText(name, &value)) {
        field.setValue(value);
        config::setValue(field, value);
    }
    END_WIDGET();
}

template <typename T>
void ConfigSliderInt(const char* name, ConfigField<T>& field, const int min, const int max, const char* description = nullptr) {
    T& value = field.getValue();

    if (ImGui::SliderInt(name, &value, min, max)) {
        field.setValue(value);
        config::setValue(field, value);
    }
    END_WIDGET();
}

template <typename T>
void ConfigDragInt(const char* name, ConfigField<T>& field, const int step, const int min, const int max, const char* description = nullptr) {
    T& value = field.getValue();

    if (ImGui::DragInt(name, &value, (float) step, min, max, nullptr, ImGuiSliderFlags_AlwaysClamp)) {
        field.setValue(value);
        config::setValue(field, value);
    }
    END_WIDGET();
}

template <typename T>
void ConfigSliderFloat(const char* name, ConfigField<T>& field, const float min, const float max, const char* description = nullptr) {
    T& value = field.getValue();

    if (ImGui::SliderFloat(name, &value, min, max)) {
        field.setValue(value);
        config::setValue(field, value);
    }
    END_WIDGET();
}

void AddUnderLine(ImColor col_);
void TextURL(const char* name_, const char* URL_, bool SameLineBefore_, bool SameLineAfter_);
