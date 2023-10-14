#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "../Json/json.hpp"
#include "../Utils/util.h"
#include "ConfigField.h"

using json = nlohmann::json;

static json configRoot;

namespace config {
    void save(json config);

    template <typename T>
    ConfigField<T> getValue(const std::string& path, const std::string& key, const T& defaultValue) {
        auto section = path;
        std::ifstream configFile("minty");

        configFile >> configRoot;
        configFile.close();

        if (section.find(":") != std::string::npos) {
            auto sectionParts = util::split(section, ":");

            for (auto& part : sectionParts)
                configRoot = configRoot[part];

            if (configRoot.find(key) != configRoot.end())
                return ConfigField<T>(path, key, configRoot[key]);
        }

        if (configRoot.find(section) != configRoot.end() && configRoot[section].find(key) != configRoot[section].end())
            return ConfigField<T>(path, key, configRoot[section][key]);
        return ConfigField<T>(path, key, defaultValue);
    }

    template<typename T>
    void setValue(const std::string& path, const std::string key, const T& newValue) {
        /*std::ifstream configFile("minty");

        configFile >> configRoot;
        configFile.close();

        if (path.find(":") != std::string::npos) {
            auto sections = util::split(path, ":");

            for (auto& section : sections)
                configRoot = configRoot[section];

            if (configRoot.find(key) != configRoot.end()) {
                configRoot[key] = newValue;
                save(configRoot);
            }
            return;
        }

        configRoot[path][key] = newValue;
        save(configRoot);*/
    }

    template<typename T>
    void setValue(ConfigField<T>& field, const T& newValue) {
        setValue(field.getPath(), field.getKey(), newValue);
    }
}
