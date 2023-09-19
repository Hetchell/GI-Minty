#pragma once
#include "../Config/ConfigManager.hpp"

class Hotkey
{
public:
	unsigned int m_nHkey;
	bool bWaitsInput = false;
	const char* hotkeyJsonName;

	Hotkey();
	Hotkey(const char* jsonStateName);

	bool IsPressed();
	void Draw(const char* label);
	void Rebind();
};