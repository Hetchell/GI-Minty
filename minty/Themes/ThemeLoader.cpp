#include "Themeloader.hpp"

void LoadThemes() {
    int style = config::getValue("general:theme", "style", 1).getValue();
    int color = config::getValue("general:theme", "color", 1).getValue();

    setTheme(color);
    setStyle(style);
    
    util::log(M_Info, "Loading theme %i, %i", style, color);
}

void LoadFonts() {
    util::log(M_Info, "Loading font (name here)");
}
