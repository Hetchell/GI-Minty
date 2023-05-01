#pragma once
#include "../ImGui/ImGui/imgui.h"
#include <Windows.h>
#include "../GUI/GuiDefinitions.h"

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
			ShellExecute(0, 0, URL_, 0, 0, SW_SHOW);
		}
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
		ImGui::SetTooltip("Open in browser\n%s", URL_);
	} else {
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_Button]);
	}
	if (SameLineAfter_) { ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x); }
}

void ShowDebugLog() {
	ImGuiTextFilter Filter;
	ImGui::Begin("Log", &show_debug_log);
	if (ImGui::SmallButton("[Debug] Add 5 entries")) {
		static int counter = 0;
		const char* categories[3] = { "Info", "Warning", "Error" };
		const char* words[] = { "virus", "sob", "leak", "plead", "windsensinden", "windy", "ril", "fek" };
		for (int n = 0; n < 5; n++) {
			const char* category = categories[counter % IM_ARRAYSIZE(categories)];
			const char* word = words[counter % IM_ARRAYSIZE(words)];
			log_textbuf.appendf("[Minty:%s] [%05d] Hello, current time is %.1f, here's a word: '%s'\n", category, ImGui::GetFrameCount(), ImGui::GetTime(), word);
			counter++;
		}
	}
	ImGui::SameLine();

	if (ImGui::SmallButton("Clear")) { log_textbuf.clear(); }

	ImGui::SameLine();

	if (ImGui::SmallButton("Copy")) { ImGui::SetClipboardText(log_textbuf.begin()); }

	Filter.Draw("Filter");
	ImGui::Separator();
	
	ImGui::BeginChild("LogScroll", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	if (Filter.IsActive()) {
		const char* buf_begin = log_textbuf.begin();
		const char* buf_end = log_textbuf.end();
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
		ImGui::TextUnformatted(log_textbuf.begin(), log_textbuf.end());
	}

	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) { ImGui::SetScrollHereY(1.0f); }

	ImGui::EndChild();	
	ImGui::End();
}

