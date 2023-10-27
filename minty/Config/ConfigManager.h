#pragma once

#include <string>
#include <fstream>

#include "ConfigField.h"
#include "../Utils/util.h"
#include "../Utils/Logger.h"
#include "../api/json/json.hpp"

using json = nlohmann::json;

namespace config {
    void save(json config);

    template <typename T>
    ConfigField<T> getValue(const std::string& path, const std::string& key, const T& defaultValue) {
        std::ifstream configFile("minty.json");
        json configRoot;

        configFile >> configRoot;
        configFile.close();

        if (path.find(":") != std::string::npos) {
            auto sections = util::split(path, ":");

            for (auto& section : sections)
                configRoot = configRoot[section];

            if (configRoot.find(key) != configRoot.end())
                return ConfigField<T>(path, key, configRoot[key]);
        }

        if (configRoot.find(path) != configRoot.end() && configRoot[path].find(key) != configRoot[path].end())
            return ConfigField<T>(path, key, configRoot[path][key]);
        return ConfigField<T>(path, key, defaultValue);
    }

    template<typename T>
    void setValue(const std::string& path, const std::string& key, const T& newValue) {
        std::ifstream configFile("minty.json");
        json configRoot;
        
        configFile >> configRoot;
        configFile.close();

        json* configTemp = &configRoot;

        if (path.find(":") != std::string::npos) {
            auto sections = util::split(path, ":");

            for (auto& section : sections) {
                if (!configTemp->contains(section))
                    (*configTemp)[section] = {};

                configTemp = &(*configTemp)[section];
            }

            (*configTemp)[key] = newValue;
            save(configRoot);
            return;
        }

        configRoot[path][key] = newValue;
        save(configRoot);
    }

    template<typename T>
    void setValue(ConfigField<T>& field, const T& newValue) {
        setValue(field.getPath(), field.getKey(), newValue);
    }
}
