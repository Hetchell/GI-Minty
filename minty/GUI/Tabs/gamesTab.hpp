#include "../MainGUI.h"
#include "../../Utils/ExtraGuiFuncs.hpp"
#include "../GuiVarDefs.h"
using namespace std;

void BeginGamesTab() {
    if (ImGui::BeginTabItem("Games"))
    {
        ImGui::SeparatorText("Lights out");
        //lightsout_main();

        ImGui::SeparatorText("Tic Tac Toe");
            
        //tictactoe_main();

        ImGui::SeparatorText("");

        //wordle_main();
            
        ImGui::EndTabItem();
    }
}