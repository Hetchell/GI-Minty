#include "ConfigManager.h"

namespace config {
    void save(json config) {
        std::ofstream configFile("minty");

        configFile << config.dump(4);
        configFile.close();
    }
}
