#include <iostream>
#include <fstream>

#include "../ImGui/ImGui/imgui.h"
#include "../Utils/Utils.hpp"
#include "../Json/json.hpp"

#include "Themes.hpp"

void LoadThemes() {
    std::ifstream config_file("minty.json");
    nlohmann::json config_json;
    config_file >> config_json;
    config_file.close();

    int style = config_json["theme"]["style"];
    int color = config_json["theme"]["color"];

    settheme(color);
    setstyle(style);
    
    util::log(M_Info, "Loading theme %i, %i", style, color);
}
void LoadFonts() {
    util::log(M_Info, "Loading font (name here)");
}
