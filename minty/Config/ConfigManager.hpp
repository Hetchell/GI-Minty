#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "../Json/json.hpp"

using namespace std;
using json = nlohmann::json;

static json configRoot;

namespace {
    std::vector<std::string> split(const std::string& content, const std::string& delimiter)
    {
        std::vector<std::string> tokens;
        size_t pos = 0;
        size_t prevPos = 0;
        std::string token;

        while ((pos = content.find(delimiter, prevPos)) != std::string::npos) {
            token = content.substr(prevPos, pos - prevPos);
            tokens.push_back(token);
            prevPos = pos + delimiter.length();
        }

        tokens.push_back(content.substr(prevPos));
        return tokens;
    }
}

namespace config {
    void save(json config);

    template <typename T>
    T getValue(const string& section, const string& key, const T& defaultValue) {
        ifstream configFile("minty.json");

        configFile >> configRoot;
        configFile.close();

        auto container = configRoot;

        if (section.find(":") != string::npos) {
            auto sectionParts = split(section, ":");

            for (auto& part : sectionParts)
                configRoot = configRoot[part];

            if (configRoot.find(key) != configRoot.end())
                return configRoot[key];
        }

        if (configRoot.find(section) != configRoot.end() && configRoot[section].find(key) != configRoot[section].end())
            return configRoot[section][key];

        configRoot[section][key] = defaultValue;
        return defaultValue;
    }

    template<typename T>
    void setValue(const string& section, const string& key, const T& value) {
        ifstream configFile("minty.json");

        configFile >> configRoot;
        configFile.close();

        configRoot[section][key] = value;
        save(configRoot);
    }
}