#include "../MainGUI.h"
#include "../../Utils/ExtraGuiFuncs.hpp"
#include "../GuiVarDefs.h"

void BeginAboutTab() {
    if (ImGui::BeginTabItem("About"))
    {
        // Content for About
        ImGui::Text("Minty BETA v0.7.1 WIP");
        ImGui::Text("ImGui version: %s", ImGui::GetVersion());

        ImVec4 linkColor = ImVec4(34.0f/255.0f, 132.0f/255.0f, 230.0f/255.0f, 1.0f);

        ImGui::Text("Contributors: мятный пряник#0086, Moistcrafter#9172, yarik#4571, azzu#2731");
        ImGui::Separator();

        ImGui::TextColored(linkColor, "KWT Team Discord (click)");
        if (ImGui::IsItemClicked()) {
            system("start https://discord.gg/kj7PQrr6CV");
        }
        ImGui::TextColored(linkColor, "KWT Team GitHub (click)");
        if (ImGui::IsItemClicked()) {
            system("start https://github.com/kindawindytoday");
        }
        ImGui::Separator();

        ImGui::EndTabItem();
    }
}