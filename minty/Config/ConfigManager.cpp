#include "ConfigManager.hpp"

namespace config {
    void save(json config) {
        ofstream configFile("minty.json");

        configFile << config.dump(4);
        configFile.close();
    }
}
