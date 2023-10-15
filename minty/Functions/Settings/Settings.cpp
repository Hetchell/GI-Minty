#include "Settings.h"

namespace cheat {
    static void DrawFPS();

    Settings::Settings() {
        f_ShowFps = config::getValue("functions:Settings", "showFps", true);
        f_ShowRpc = config::getValue("functions:Settings", "showRpc", true);
        f_InitDelay = config::getValue("functions:Settings", "initDelay", 15000);
        f_animationDuration = config::getValue("functions:Settings", "animationDuration", 0.2f);
    }

    Settings& Settings::getInstance() {
        static Settings instance;
        return instance;
    }

	void Settings::GUI() {
        ImGui::SeparatorText("General");

        ConfigCheckbox("Show current FPS", f_ShowFps);
        ConfigCheckbox("Show Discord RPC", f_ShowRpc);
        ImGui::SameLine();
        HelpMarker("Turn Discord custom RPC on/off. Requires re-entering game.");

        ConfigSliderInt("Initialization delay (ms)", f_InitDelay, 0, 60000);
        ImGui::SameLine(); 
        HelpMarker("Change delay before showing menu. May cause lags while opening, so try to change this value in case.");

        ImGui::SeparatorText("Theme");

        static int themeIndex = 1;
        if (ImGui::RadioButton("Dark", &themeIndex, 1)) {
            setTheme(1);
            config::setValue("general:theme", "color", 1);
        }

        if (ImGui::RadioButton("Light", &themeIndex, 2)) {
            setTheme(2);
            config::setValue("general:theme", "color", 2);
        }

        ImGui::SeparatorText("Style");

        static int themestyleindex = 1;
        if (ImGui::RadioButton("Cozy", &themestyleindex, 1)) {
            setStyle(1);
            config::setValue("theme", "style", 1);
        }

        if (ImGui::RadioButton("Cozy Squared", &themestyleindex, 2)) {
            setStyle(2);
            config::setValue("theme", "style", 2);
        }

        ImGui::SeparatorText("Font");

        static int fontSelectionIndex = 0;
        if (ImGui::RadioButton("Normal", &fontSelectionIndex, 0))
            setFont(1);

        if (ImGui::RadioButton("Bold", &fontSelectionIndex, 1))
            setFont(2);

        ImGui::SeparatorText("Customize");
        ImGui::Checkbox("Show Style Editor", &show_style_editor);

        ConfigSliderFloat("Duration of animation (s)", f_animationDuration, 0, 5.f);
        ImGui::SameLine();
        HelpMarker(_("Window appearance animation duration."));

	}

    void Settings::Outer() {
        if (f_ShowFps.getValue())
            DrawFPS();
    }

    std::string Settings::getModule() {
        return _("Settings");
    }

    void DrawFPS() {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("##FPS", NULL, flags);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
