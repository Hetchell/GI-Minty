#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../ImGui/ImGui/imgui.h"
#include <Windows.h>
#include "../GUI/GuiDefinitions.h"
#include "../ImGui/ImGui/imgui_internal.h"

static void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

// Header
namespace ImGui {
    bool ColoredButtonV1(const char* label, const ImVec2& size, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2);
}

void AddUnderLine(ImColor col_) {
	ImVec2 min = ImGui::GetItemRectMin();
	ImVec2 max = ImGui::GetItemRectMax();
	min.y = max.y;
	ImGui::GetWindowDrawList()->AddLine(min, max, col_, 1.0f);
}

void TextURL(const char* name_, const char* URL_, bool SameLineBefore_, bool SameLineAfter_) {
	if (SameLineBefore_) { ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x); }
	ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
	ImGui::Text(name_);
	ImGui::PopStyleColor();
	if (ImGui::IsItemHovered()) {
		if (ImGui::IsMouseClicked(0)) {
			ShellExecuteA(0, 0, URL_, 0, 0, SW_SHOW);
		}
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
		ImGui::SetTooltip("Open in browser\n%s", URL_);
	} else {
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_Button]);
	}
	if (SameLineAfter_) { ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x); }
}

static ImGuiTextBuffer log_textbuf1;

void ShowDebugLog() {
	ImGuiTextFilter Filter;
    static bool show_debug_log;
	ImGui::Begin("Log", &show_debug_log);
	if (ImGui::SmallButton("[Debug] Add 5 entries")) {
		static int counter = 0;
		const char* categories[3] = { "Info", "Warning", "Error" };
		const char* words[] = { "virus", "sob", "leak", "plead", "windsensinden", "windy", "ril", "fek" };
		for (int n = 0; n < 5; n++) {
			const char* category = categories[counter % IM_ARRAYSIZE(categories)];
			const char* word = words[counter % IM_ARRAYSIZE(words)];
			log_textbuf1.appendf("[Minty:%s] [%05d] Hello, current time is %.1f, here's a word: '%s'\n", category, ImGui::GetFrameCount(), ImGui::GetTime(), word);
			counter++;
		}
	}

	ImGui::SameLine();

	if (ImGui::SmallButton("Clear")) { log_textbuf1.clear(); }

	ImGui::SameLine();

	if (ImGui::SmallButton("Copy")) { ImGui::SetClipboardText(log_textbuf1.begin()); }

	Filter.Draw("Filter");
	ImGui::Separator();
	
	ImGui::BeginChild("LogScroll", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	if (Filter.IsActive()) {
		const char* buf_begin = log_textbuf1.begin();
		const char* buf_end = log_textbuf1.end();
		ImGuiTextBuffer log_filtered;
		while (buf_begin < buf_end) {
			const char* line_end = strchr(buf_begin, '\n');
			if (Filter.PassFilter(buf_begin, line_end)) {
				log_filtered.append(buf_begin, line_end);
				log_filtered.append("\n");
			}
			buf_begin = line_end + 1;
		}
		ImGui::TextUnformatted(log_filtered.begin(), log_filtered.end());
	}
	else {
		ImGui::TextUnformatted(log_textbuf1.begin(), log_textbuf1.end());
	}

	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) { ImGui::SetScrollHereY(1.0f); }

	ImGui::EndChild();	
	ImGui::End();
}

// Implementation
bool ImGui::ColoredButtonV1(const char* label, const ImVec2& size_arg, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    ImGuiButtonFlags flags = ImGuiButtonFlags_None;
    if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    // Render
    const bool is_gradient = bg_color_1 != bg_color_2;
    if (held || hovered)
    {
        // Modify colors (ultimately this can be prebaked in the style)
        float h_increase = (held && hovered) ? 0.02f : 0.02f;
        float v_increase = (held && hovered) ? 0.20f : 0.07f;

        ImVec4 bg1f = ColorConvertU32ToFloat4(bg_color_1);
        ColorConvertRGBtoHSV(bg1f.x, bg1f.y, bg1f.z, bg1f.x, bg1f.y, bg1f.z);
        bg1f.x = ImMin(bg1f.x + h_increase, 1.0f);
        bg1f.z = ImMin(bg1f.z + v_increase, 1.0f);
        ColorConvertHSVtoRGB(bg1f.x, bg1f.y, bg1f.z, bg1f.x, bg1f.y, bg1f.z);
        bg_color_1 = GetColorU32(bg1f);
        if (is_gradient)
        {
            ImVec4 bg2f = ColorConvertU32ToFloat4(bg_color_2);
            ColorConvertRGBtoHSV(bg2f.x, bg2f.y, bg2f.z, bg2f.x, bg2f.y, bg2f.z);
            bg2f.z = ImMin(bg2f.z + h_increase, 1.0f);
            bg2f.z = ImMin(bg2f.z + v_increase, 1.0f);
            ColorConvertHSVtoRGB(bg2f.x, bg2f.y, bg2f.z, bg2f.x, bg2f.y, bg2f.z);
            bg_color_2 = GetColorU32(bg2f);
        }
        else
        {
            bg_color_2 = bg_color_1;
        }
    }
    RenderNavHighlight(bb, id);

#if 0
    // V1 : faster but prevents rounding
    window->DrawList->AddRectFilledMultiColor(bb.Min, bb.Max, bg_color_1, bg_color_1, bg_color_2, bg_color_2);
    if (g.Style.FrameBorderSize > 0.0f)
        window->DrawList->AddRect(bb.Min, bb.Max, GetColorU32(ImGuiCol_Border), 0.0f, 0, g.Style.FrameBorderSize);
#endif

    // V2
    int vert_start_idx = window->DrawList->VtxBuffer.Size;
    window->DrawList->AddRectFilled(bb.Min, bb.Max, bg_color_1, g.Style.FrameRounding);
    int vert_end_idx = window->DrawList->VtxBuffer.Size;
    if (is_gradient)
        ShadeVertsLinearColorGradientKeepAlpha(window->DrawList, vert_start_idx, vert_end_idx, bb.Min, bb.GetBL(), bg_color_1, bg_color_2);
    if (g.Style.FrameBorderSize > 0.0f)
        window->DrawList->AddRect(bb.Min, bb.Max, GetColorU32(ImGuiCol_Border), g.Style.FrameRounding, 0, g.Style.FrameBorderSize);

    if (g.LogEnabled)
        LogSetNextTextDecoration("[", "]");
    PushStyleColor(ImGuiCol_Text, text_color);
    RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
    PopStyleColor();

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return pressed;
}

//void CreateFuncWidget(const char* label_checkbox, static bool isChecked, const char* helpText, const char* label_slider, static float f_value, static float f_valueOrigin, float min_cap, float max_cap, void (*il2FN)(int32_t)) { // slider float -------  some c-+= bugs again, tons of errors
//    f_value = f_valueOrigin;
//    ImGui::Checkbox(label_checkbox, &isChecked);
//    ImGui::SameLine();
//    HelpMarker(helpText);
//    if (isChecked) {
//        ImGui::Indent();
//        if (ImGui::SliderFloat(label_slider, &f_value, min_cap, max_cap, "%.3f")) {
//            il2FN(f_value);
//        }
//        ImGui::Unindent();
//    }
//}
//
//void CreateFuncWidget(const char* label_checkbox, static bool isChecked, static bool isSameline, const char* label_execbutton, const char* helpText, const char* label_slider, static float f_value, static float f_valueOrigin, float min_cap, float max_cap, void (*il2FN)(int32_t)) { // slider float
//    f_value = f_valueOrigin;
//    ImGui::Checkbox(label_checkbox, &isChecked);
//    ImGui::SameLine();
//    HelpMarker(helpText);
//    if (isChecked) {
//        ImGui::Indent();
//        ImGui::SliderFloat(label_slider, &f_value, min_cap, max_cap, "%.3f");
//        if (isSameline)
//            ImGui::SameLine();
//        if (ImGui::Button(label_execbutton)) {
//            il2FN(f_value);
//        }
//        ImGui::Unindent();
//    }
//}
//
//void CreateFuncWidget(const char* label) { // just button (idk how to realize it)
//
//}
//void CreateFuncWidget(const char* label, static bool b_value) { // checkbox (same)
//
//}