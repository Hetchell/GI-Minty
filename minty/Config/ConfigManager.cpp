#include "ConfigManager.hpp"

nlohmann::json cfgjsonobj;

void saveFuncStateToJson(std::string funcName, bool state) {
    /*std::ifstream config_file("minty");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    cfgjsonobj["functions"][funcName] = state;
    config_json.merge_patch(cfgjsonobj);
    std::ofstream merged_file("minty");
    merged_file << config_json.dump(4);
    merged_file.close();*/
}

void saveFuncStateToJson(std::string funcName, float state) {
    std::ifstream config_file("minty.json");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    cfgjsonobj["functions"][funcName] = state;
    config_json.merge_patch(cfgjsonobj);
    std::ofstream merged_file("minty.json");
    merged_file << config_json.dump(4);
    merged_file.close();
}

void saveFuncStateToJson(std::string funcName, int state) {
    std::ifstream config_file("minty.json");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    cfgjsonobj["functions"][funcName] = state;
    config_json.merge_patch(cfgjsonobj);
    std::ofstream merged_file("minty.json");
    merged_file << config_json.dump(4);
    merged_file.close();
}

bool readBoolFuncStateFromJson(std::string funcName) {
    std::ifstream config_file("minty.json");
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

template <typename T, typename... Args>
T getSmthFromJson(const T& defaultValue, const Args&... args) {
    try {
        std::ifstream config_file("minty.json");
        nlohmann::json config_json;
        config_file >> config_json;
        config_file.close();

        nlohmann::json* currentNode = &config_json;
        // Traverse through the key parts
        ((currentNode = &(*currentNode)[args]), ...);

        if (currentNode->is_null()) {
            return defaultValue;
        }

        return currentNode->get<T>();
    }
    catch (nlohmann::json::exception e) {
        std::cout << e.what();
        return defaultValue;
    }
}

template <typename T, typename... Args>
void saveSmthToJson(const T& value, const Args&... args) {
    try {
        std::ifstream config_file("minty.json");
        nlohmann::json config_json;
        config_file >> config_json;
        config_file.close();

        nlohmann::json* currentNode = &config_json;
        const auto lastKey = std::get<sizeof...(Args) - 1>(std::make_tuple(args...));

        // Traverse through the key parts except the last one
        ((currentNode = &(*currentNode)[args]), ...);

        // Set the value using the last key
        (*currentNode)[lastKey] = value;

        std::ofstream merged_file("minty.json");
        merged_file << config_json.dump(4);
        merged_file.close();
    }
    catch (nlohmann::json::exception e) {
        std::cout << e.what();
    }
}

