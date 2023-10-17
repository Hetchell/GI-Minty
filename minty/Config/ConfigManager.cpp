#include "ConfigManager.h"

namespace config {
    void save(json config) {
        std::ofstream configFile("minty.json");

        configFile << config.dump(4) << "\n";
        configFile.close();
    }
}
