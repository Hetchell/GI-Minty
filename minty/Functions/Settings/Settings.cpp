#include "Settings.h"

namespace cheat {
	void Settings::GUI() {
        initDelay = config::getValue("general", "initDelay", 15000);
        bool show_rpc = config::getValue("general", "showRPC", true);

        ImGui::SeparatorText("General");

        ImGui::Checkbox("Show ImGui's cursor", &ImGui::GetIO().MouseDrawCursor);

        if (ImGui::Checkbox("Show current FPS", &ifShowFPS)) {
            config::setValue("general", "ShowFPS", ifShowFPS);
        }

        //ImGui::Checkbox("Block input", &block_input);

        if (ImGui::Checkbox("Show Discord RPC", &show_rpc)) {
            config::setValue("general", "showRPC", show_rpc);
        }
        ImGui::SameLine(); 
        HelpMarker("Turn Discord custom RPC on/off. Requires re-entering game.");

        if (ImGui::SliderInt("Initialization delay (ms)", &initDelay, 0, 60000)) {
            config::setValue("general", "initDelay", initDelay);
        }
        ImGui::SameLine(); 
        HelpMarker("Change delay before showing menu. May cause lags while opening, so try to change this value in case.");

        ImGui::SeparatorText("Theme");
        /*----------PLACEHOLDER----------*/
        static int themeIndex = 1;

        if (ImGui::RadioButton("Dark", &themeIndex, 1)) {
            settheme(1);
            config::setValue("theme", "color", 1);

        }

        if (ImGui::RadioButton("Light", &themeIndex, 2)) {
            settheme(2);
            config::setValue("theme", "color", 2);

        }

        /*if (ImGui::RadioButton("Red", &themeIndex, 3)) {
            settheme(3);
            cfgjsonobj["theme"]["color"] = 3;
            config_json.merge_patch(cfgjsonobj);
            std::ofstream merged_file("minty");
            merged_file << config_json.dump(4);
            merged_file.close();
        }*/

        ImGui::SeparatorText("Style");

        static int themestyleindex = 1;

        if (ImGui::RadioButton("Cozy", &themestyleindex, 1)) {
            setstyle(1);
            config::setValue("theme", "style", 1);

        }

        if (ImGui::RadioButton("Cozy Squared", &themestyleindex, 2)) {
            setstyle(2);
            config::setValue("theme", "style", 2);

        }

        ImGui::SeparatorText("Font");

        static int fontSelectionIndex = 0;
        if (ImGui::RadioButton("Normal", &fontSelectionIndex, 0)) {
            setfont(1);
        }

        if (ImGui::RadioButton("Bold", &fontSelectionIndex, 1)) {
            setfont(2);
        }

        ImGui::SeparatorText("Customize");
        //ImGui::TextDisabled("DEBUG");
        ImGui::Checkbox("Show Style Editor", &show_style_editor);
	}
}