#include "ConfigManager.hpp"

nlohmann::json cfgjsonobj;

void saveFuncStateToJson(std::string funcName, bool state) {
    std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    cfgjsonobj["functions"][funcName] = state;
    config_json.merge_patch(cfgjsonobj);
    std::ofstream merged_file("minty");
    merged_file << config_json.dump(4);
    merged_file.close();
}

void saveFuncStateToJson(std::string funcName, float state) {
    std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    cfgjsonobj["functions"][funcName] = state;
    config_json.merge_patch(cfgjsonobj);
    std::ofstream merged_file("minty");
    merged_file << config_json.dump(4);
    merged_file.close();
}

void saveFuncStateToJson(std::string funcName, int state) {
    std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    cfgjsonobj["functions"][funcName] = state;
    config_json.merge_patch(cfgjsonobj);
    std::ofstream merged_file("minty");
    merged_file << config_json.dump(4);
    merged_file.close();
}

bool readBoolFuncStateFromJson(std::string funcName) {
    std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    if (config_json["functions"][funcName] == true) {
        return true;
    }
    else {
        return false;
    }
}

int readHotkeyFromJson(std::string hotkeyName)
{
    std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    return config_json["hotkeys"][hotkeyName];
}

void saveHotkeyToJson(std::string hotkeyName, int hotkey)
{
    std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    cfgjsonobj["hotkeys"][hotkeyName] = hotkey;
    config_json.merge_patch(cfgjsonobj);
    std::ofstream merged_file("minty");
    merged_file << config_json.dump(4);
    merged_file.close();
}
