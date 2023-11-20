#include "ThemeLoader.h"

void LoadThemes() {
    int style = config::getValue("general:theme", "style", 1).getValue();
    int color = config::getValue("general:theme", "color", 1).getValue();

    setTheme(color);
    setStyle(style);
    
    LOG_INFO("Loading theme %i, %i", style, color);
}

void LoadFonts() {
    LOG_INFO("Loading font");
}
