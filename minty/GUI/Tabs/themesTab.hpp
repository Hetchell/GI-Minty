#include "../MainGUI.h"
#include "../../Utils/ExtraGuiFuncs.hpp"
#include "../GuiVarDefs.h"

void BeginThemesTab() {
    
            if (ImGui::BeginTabItem("Themes"))
            {
                // Content for themes
                ImGui::Text("Theme colors");

                static int themeIndex = 0;

                if (ImGui::RadioButton("Default dark", &themeIndex, 0))
                {
                    settheme(1);
                }

                if (ImGui::RadioButton("Default light", &themeIndex, 1))
                {
                    settheme(2);
                }

                if (ImGui::RadioButton("Default classic", &themeIndex, 2))
                {
                    settheme(3);
                }

                if (ImGui::RadioButton("Dark theme", &themeIndex, 3))
                {
                    settheme(4);
                }

                if (ImGui::RadioButton("Minty Red", &themeIndex, 4))
                {
                    settheme(5);
                }
                
                if (ImGui::RadioButton("Minty Mint", &themeIndex, 5))
                {
                    settheme(6);
                }

                if (ImGui::RadioButton("Minty Mint Light", &themeIndex, 6))
                {
                    settheme(7);
                }

                ImGui::Separator();
                ImGui::Text("Theme style");

                static int themestyleindex = 0;

                if (ImGui::RadioButton("Rounded compact style", &themestyleindex, 0))
                {
                    setstyle(1);
                }
                
                if (ImGui::RadioButton("Big", &themestyleindex, 1))
                {
                    setstyle(2);
                }

                if (ImGui::RadioButton("ImGui Default", &themestyleindex, 2))
                {
                    setstyle(3);
                }

                if (ImGui::RadioButton("Big Squared", &themestyleindex, 3))
                {
                    setstyle(4);
                }

                ImGui::Separator();

                ImGui::Text("Menu font");

                static int fontSelectionIndex = 0;
                if (ImGui::RadioButton("Jetbrains Mono", &fontSelectionIndex, 0))
                {
                    setfont(1);
                }

                if (ImGui::RadioButton("Myriad Pro", &fontSelectionIndex, 1))
                {
                    setfont(2);
                }

                ImGui::Separator();

                ImGui::Text("Style Editor");

                ImGui::Checkbox("Show Style Editor", &show_style_editor);

                ImGui::EndTabItem();
            }
}