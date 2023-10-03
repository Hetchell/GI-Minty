#pragma once
#include "../Config/ConfigManager.hpp"
#include <chrono>

namespace {
    nlohmann::json cfgjsonobj;
    int readHotkeyFromJson(std::string hotkeyName)
    {
        try {
            std::ifstream config_file("minty.json");
            nlohmann::json config_json;
            config_file >> config_json;
            config_file.close();

            return config_json["hotkeys"][hotkeyName];
        }
        catch (nlohmann::json::exception e) {
            std::cout << e.what();
        }
    }

    void saveHotkeyToJson(std::string hotkeyName, int hotkey)
    {
        std::ifstream config_file("minty.json");
        nlohmann::json config_json;
        config_file >> config_json;
        config_file.close();

        cfgjsonobj["hotkeys"][hotkeyName] = hotkey;
        config_json.merge_patch(cfgjsonobj);
        std::ofstream merged_file("minty.json");
        merged_file << config_json.dump(4);
        merged_file.close();
    }
}

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