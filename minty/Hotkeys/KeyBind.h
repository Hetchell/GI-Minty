#pragma once
#include "KeyBinds.h"
#include <fstream>

namespace KeyBind
{
	bool IsKeyPressed(unsigned int k) noexcept;
	bool SetToPressedKey(unsigned int* key, const char* hotkeyJsonName) noexcept;
};