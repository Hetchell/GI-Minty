#include "../MainGUI.h"
#include "../../Utils/ExtraGuiFuncs.hpp"
#include "../GuiVarDefs.h"

void BeginDebugTab() {
    if (ImGui::BeginTabItem("Debug"))
    {
        ImGui::Checkbox("Show Debug Metrics", &show_debug_metrics);
        ImGui::EndTabItem();
    }
}