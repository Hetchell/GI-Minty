#include "Settings.h"

namespace cheat {
    static void DrawFPS();

    Settings::Settings() {
        f_DisableProtection = config::getValue("functions:Settings", "disableProtection", true);
        f_DisableLog = config::getValue("functions:Settings", "disableLog", true);
        f_SpoofACResult = config::getValue("functions:Settings", "spoofACResult", true);
        f_UseSignature = config::getValue("functions:Settings", "useSignature", false);
        f_ShowFps = config::getValue("functions:Settings", "showFps", true);
        f_ShowRpc = config::getValue("functions:Settings", "showRpc", true);
        f_InitDelay = config::getValue("functions:Settings", "initDelay", 15000);
        f_StartupArguments = config::getValue<std::string>("functions:Settings", "startupArguments", "");
        f_AnimationDuration = config::getValue("functions:Settings", "animationDuration", 0.2f);
        f_Hotkey = Hotkey("functions:Settings:Menu", VK_F12);

        f_ShowMenu = true;
    }

    Settings& Settings::getInstance() {
        static Settings instance;
        return instance;
    }

    void Settings::GUI() {
        ImGui::SeparatorText("General");

        f_Hotkey.Draw();
        ImGui::SameLine();
        HelpMarker("Show the Minty Menu.");

        ConfigCheckbox("Disable protection", f_DisableProtection, "Close anitcheat handle.\n(changes will take effect after relaunch).");
        ConfigCheckbox("Disable analytic log", f_DisableLog, "Disable game telemetry and analytic log from spamming the console.\n"
            "(changes will take effect after relaunch).");
        ConfigCheckbox("Spoof anticheat result", f_SpoofACResult, "Spoofs/Blocks anticheat reports made by WindSeedClientNotify.\n"
            "(changes will take effect after relaunch).");
        ConfigCheckbox("Use predefined file signature", f_UseSignature, "Uses 'hardcoded' signature value for file check.\n"
            "Can be useful, when you put the additional executable files to game directory.\n"
            "And can't pass the 'Integrity check' on login.\n"
            "(changes will take effect after relaunch).");

        ConfigCheckbox("Show current FPS", f_ShowFps, "Shows the current FPS.");
        ConfigCheckbox("Show Discord RPC", f_ShowRpc, "Shows the Discord RPC.\n(changes will take effect after relaunch).");

        ConfigSliderInt("Initialization delay (ms)", f_InitDelay, 0, 60000,
            "Change delay before showing menu.\nMay cause lags while opening, so try to change this value in case.");

        ConfigInputText("Startup arguments", f_StartupArguments, "Launch the game with command line arguments.\n"
            "(changes will take effect after relaunch).");
        TextURL("List of unity command line arguments", "https://docs.unity3d.com/Manual/PlayerCommandLineArguments.html", false, false);

        ImGui::SeparatorText("Theme");

        static int themeIndex = 1;
        if (ImGui::RadioButton("Dark", &themeIndex, 1))
            setTheme(1);

        if (ImGui::RadioButton("Light", &themeIndex, 2))
            setTheme(2);

        ImGui::SeparatorText("Style");

        static int styleIndex = 1;
        if (ImGui::RadioButton("Cozy", &styleIndex, 1))
            setStyle(1);

        if (ImGui::RadioButton("Cozy Squared", &styleIndex, 2))
            setStyle(2);

        ImGui::SeparatorText("Font");

        static int fontIndex = 0;
        if (ImGui::RadioButton("Normal", &fontIndex, 0))
            setFont(1);

        if (ImGui::RadioButton("Bold", &fontIndex, 1))
            setFont(2);

        ImGui::SeparatorText("Customize");
        ImGui::Checkbox("Show Style Editor", &show_style_editor);
        ConfigSliderFloat("Duration of animation (s)", f_AnimationDuration, 0, 5.0f,
            "Window appearance animation duration.");
	}

    void Settings::Outer() {
        if (f_Hotkey.IsPressed())
            f_ShowMenu = !f_ShowMenu;

        if (f_ShowFps.getValue())
            DrawFPS();

        if (show_style_editor) {
            ImGui::Begin("Style Editor", &show_style_editor);
            ImGui::ShowStyleEditor();
            ImGui::End();
        }
    }

    std::string Settings::getModule() {
        return _("Settings");
    }

    void DrawFPS() {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("##FPS", NULL, flags);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
