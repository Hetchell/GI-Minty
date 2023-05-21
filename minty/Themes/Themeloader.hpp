#include "../ImGui/ImGui/imgui.h"
#include "../Utils/Utils.hpp"
#include "themes.hpp"
//void Loadthemes(int idk_listthing) {
void LoadThemes() {
    settheme(1);
    setstyle(1);
    
    util::log(2, "Loading theme (name here)");
}
void LoadFonts() {
    util::log(2, "Loading font (name here)");
}
