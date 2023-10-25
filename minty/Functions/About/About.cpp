#include "About.h"

namespace cheat {
    About& About::getInstance() {
        static About instance;
        return instance;
    }

	void About::GUI() {
        ImGui::SeparatorText("About");

        ImGui::Text("Minty version 1.39.54");
        ImGui::Text("ImGui version: %s", ImGui::GetVersion());
        ImGui::Text("Design made with love by KittyKate :3");

        ImGui::SeparatorText("Contributors");

        ImGui::TextColored(ImVec4(235.0F / 255.0F, 64.0F / 255.0F, 52.0F / 255.0F, 1.0), "Owner: MintyGingy");
        ImGui::TextColored(ImVec4(219.0F / 255.0F, 57.0F / 255.0F, 219.0F / 255.0F, 1.0), "Co-founder: Moistcrafter");
        ImGui::TextColored(ImVec4(57.0F / 255.0F, 68.0F / 255.0F, 219.0F / 255.0F, 1.0), "Contributors: EtoShinya, KittyKate, lilmayofuksu, USSY, akioukun, sad_akulka");
        ImGui::TextColored(ImVec4(255, 0, 212, 255), "Donaters: Thomas_Heath, Blair, unmeinoshonen, USSY");
        ImGui::TextColored(ImVec4(0, 255, 179, 255), "Special thanks to family: Futchev, yarik0chka, keitaro_gg");

        ImGui::Text("Minty Github: ");
        TextURL("Link", "https://github.com/kindawindytoday/Minty-Releases", true, false);

        ImGui::Text("KWT Discord: ");
        TextURL("Link", "https://discord.gg/kindawindytoday", true, false);
	}

    std::string About::getModule() {
        return _("About");
    }
}
