#include <Windows.h>
#include "../ImGui/ImGui/imgui.h"

#include "../ImGui/ImGui/imgui_internal.h"

#include "KeyBind.h"
#include "../Config/ConfigManager.hpp"


// Checks key press passed in first parameter
bool KeyBind::IsKeyPressed(unsigned int k) noexcept
{
	if (k == KeyCodes[0])
		return false;

	return ImGui::IsKeyPressed(static_cast<ImGuiKey>(k), false);
}


bool KeyBind::SetToPressedKey(unsigned int* key, const char* hotkeyJsonName) noexcept
{
	// fuck this, because it sucks on binding on other buttons
	Sleep(10);
	for (auto &Key : KeyCodes)
	{
		if (IsKeyPressed(VK_LBUTTON) || IsKeyPressed(VK_RBUTTON) || IsKeyPressed(VK_MENU) /* unexpected random alt presses */)
			continue;

		if (IsKeyPressed(VK_ESCAPE))
		{
			*key = KeyCodes[0];
			return true;
			break;
		}

		if (IsKeyPressed(Key)) {
			*key = Key;
			saveHotkeyToJson(hotkeyJsonName, Key);
			return true;
			break;
		}
	}
	return false;
}