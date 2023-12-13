#pragma once

#include <chrono>
#include <Windows.h>
#include <thread>

#include "../api/imgui/ImGui/imgui.h"
#include "../config/ConfigManager.h"
#include "KeyBind.h"

class Hotkey {
public:
	short key;
	const char* path;
	const char* name;
	bool waitInput = false;
	std::chrono::steady_clock::time_point lastInputTime;

	Hotkey();

	Hotkey(const char* path);
	Hotkey(const char* path, short key);
	Hotkey(const char* path, const char* name);
	Hotkey(const char* path, const char* name, short key);

	bool IsPressed();
	bool IsDown();
	void Draw(const char* label);
	void Draw();
	void Rebind();
};
