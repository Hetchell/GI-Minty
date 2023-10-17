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
        std::ifstream configFile("minty.json");

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
    void setValue(const std::string& path, const std::string key, const T& newValue) {
        //std::ifstream configFile("minty.json");

        //configFile >> configRoot;
        //configFile.close();

        //json* rootContainer = &configRoot;

        //if (path.find(":") != std::string::npos) {
        //    auto sections = util::split(path, ":");
        //    const auto lastKey = sections.back();
        //    std::cout << "lastKey: " << lastKey << "\n";

        //    for (auto& section : sections) {
        //        std::cout << "section: " << section << "\n";

        //        if (!rootContainer->contains(section)) {
        //            std::cout << "1 rootContainer: " << rootContainer->dump(4) << "\n";
        //            (*rootContainer)[section] = {};
        //            std::cout << "2 rootContainer: " << rootContainer->dump(4) << "\n";
        //        }
        //        
        //        rootContainer = &(*rootContainer)[section];
        //        //configRoot = configRoot[section];
        //        std::cout << "FINAL rootContainer: " << rootContainer->dump(4) << "\n";
        //    }

        //    //configRoot[key] = newValue;
        //    //save(configRoot);
        //    return;
        //}

        //configRoot[path][key] = newValue;
        //save(configRoot);
    }

    template<typename T>
    void setValue(ConfigField<T>& field, const T& newValue) {
        setValue(field.getPath(), field.getKey(), newValue);
    }
}
