#pragma once
#include "KeyBinds.h"

namespace KeyBind
{
	bool IsKeyPressed(unsigned int k) noexcept;
	bool SetToPressedKey(unsigned int* key, const char* hotkeyJsonName) noexcept;
};