#pragma once

#include <Windows.h>
#include <fstream>

#include "../api/imgui/ImGui/imgui.h"
#include "../config/ConfigManager.h"

namespace KeyBind {
	bool SetToPressedKey(const std::string& path, const std::string& name, short* key);

	short getPressedHotkey();
	short InputToLegacy(short inputKey);
	std::string getKeyName(short key);
	bool IsKeyDown(ImGuiKey key);
	bool IsKeyPressed(ImGuiKey key);
	ImGuiKey LegacyToInput(short key);
};
