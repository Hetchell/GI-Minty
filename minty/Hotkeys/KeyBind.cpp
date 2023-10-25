#include <Windows.h>

#include "../api/imgui/ImGui/imgui.h"
#include "../api/imgui/ImGui/imgui_internal.h"
#include "../config/ConfigManager.h"
#include "KeyBind.h"

bool KeyBind::IsKeyPressed(unsigned int k) noexcept {
	if (k == KeyCodes[0])
		return false;

	return ImGui::IsKeyPressed(static_cast<ImGuiKey>(k), false);
}

namespace {
	//nlohmann::json cfgjsonobj;
	void saveHotkeyToJson(std::string hotkeyName, int hotkey) {
		/*std::ifstream config_file("minty.json");
		nlohmann::json config_json;
		config_file >> config_json;
		config_file.close();

		cfgjsonobj["hotkeys"][hotkeyName] = hotkey;
		config_json.merge_patch(cfgjsonobj);
		std::ofstream merged_file("minty.json");
		merged_file << config_json.dump(4);
		merged_file.close();
		шо не так почему закоментированно	
		*/
	}
}

bool KeyBind::SetToPressedKey(unsigned int* key, const char* functionName) noexcept {
	// fuck this, because it sucks on binding on other buttons
	Sleep(10);

	for (auto &Key : KeyCodes) {
		if (IsKeyPressed(VK_LBUTTON) || IsKeyPressed(VK_RBUTTON) || IsKeyPressed(VK_MENU) /* unexpected random alt presses */)
			continue;

		if (IsKeyPressed(VK_ESCAPE)) {
			*key = KeyCodes[0];
			return true;
			break;
		}

		if (IsKeyPressed(Key)) {
			*key = Key;
			saveHotkeyToJson(functionName, Key);
			return true;
			break;
		}
	}
	return false;
}
