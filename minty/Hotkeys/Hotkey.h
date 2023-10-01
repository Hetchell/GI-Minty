#pragma once
#include "../Config/ConfigManager.hpp"
#include <chrono>

class Hotkey
{
public:
	unsigned int m_nHkey;
	bool bWaitsInput = false;
	const char* hotkeyJsonName;
	std::chrono::steady_clock::time_point lastInputTime;

	Hotkey();
	Hotkey(const char* jsonStateName);

	bool IsPressed();
	bool IsDown();
	void Draw();
	void Rebind();
};