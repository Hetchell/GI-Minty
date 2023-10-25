#pragma once

#include "../config/ConfigManager.h"
#include <chrono>

class Hotkey {
public:
	unsigned int m_nHkey;
	bool bWaitsInput = false;
	const char* functionName;
	std::chrono::steady_clock::time_point lastInputTime;

	Hotkey();
	Hotkey(const char* functionName);

	bool IsPressed();
	bool IsDown();
	void Draw();
	void Rebind();
};
