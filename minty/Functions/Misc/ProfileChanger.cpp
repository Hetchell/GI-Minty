#include "ProfileChanger.h"

namespace cheat {
    void onUpdate_1(app::GameManager* __this);
    void Change_UID(const char* uidText);

    static char Uid_buf[512] = "";
    ProfileChanger::ProfileChanger() {
        ifUid = config::getValue("functions", "CustomUDDDDDDID", false);

        HookManager::install(app::GameManager_Update, onUpdate_1);
    }

    ProfileChanger& ProfileChanger::getInstance()
    {
        static ProfileChanger instance;
        return instance;
    }

    void ProfileChanger::GUI() {
        CheckBoxFN("Profile Changer", ifUid, "ProfileChanger")
        if (ifUid) {
            ImGui::Indent();
            ImGui::InputText("Custom UID", Uid_buf, sizeof(Uid_buf));
            uidHotkey.Draw();
            ImGui::Unindent();
        }
    }

    void ProfileChanger::Outer() {
        if (uidHotkey.IsPressed())
            ifUid = !ifUid;
    }

    void ProfileChanger::Status() {
        if (ifUid)
            ImGui::Text("ProfileChanger");
    }

    app::GameObject* uidTextObj;
    app::Component_1* uidTextComp;
    void Change_UID(const char* uidText) {
        if (uidTextObj == nullptr)
            uidTextObj = app::UnityEngine__GameObject__Find(string_to_il2cppi("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        if (uidTextObj != nullptr && uidTextComp == nullptr)
            uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, string_to_il2cppi("Text"));

        app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), string_to_il2cppi(uidText));
    }

    void onUpdate_1(app::GameManager* __this) {
        __try {
            if (ProfileChanger::ifUid) 
                Change_UID(Uid_buf);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            util::log(M_Error, "Exception 0x%08x.", _exception_code());
        }

        CALL_ORIGIN(onUpdate_1, __this);
    }
}
