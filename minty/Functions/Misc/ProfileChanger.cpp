#include "ProfileChanger.h"

namespace cheat {
    static void InstallHooks();
    void Change_UID(const char* uidText);

    char Uid_buf[512] = "";

    ProfileChanger::ProfileChanger(): Function() {
        f_EnabledUid = config::getValue("functions:ProfileChanger:UID", "enabled", false);

        InstallHooks();
    }

    ProfileChanger& ProfileChanger::getInstance() {
        static ProfileChanger instance;
        return instance;
    }

    void ProfileChanger::GUI() {
        ConfigCheckbox("Profile Changer", f_EnabledUid);

        if (f_EnabledUid.getValue()) {
            ImGui::Indent();
            ImGui::InputText("Custom UID", Uid_buf, sizeof(Uid_buf));
            uidHotkey.Draw();
            ImGui::Unindent();
        }
    }

    void ProfileChanger::Outer() {
        if (uidHotkey.IsPressed())
            f_EnabledUid.setValue(!f_EnabledUid.getValue());
    }

    void ProfileChanger::Status() {
        if (f_EnabledUid.getValue())
            ImGui::Text("Profile Changer");
    }

    std::string ProfileChanger::getModule() {
        return _("Misc");
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

    static void onUpdate_1(app::GameManager* __this) {
        util::log(M_Debug, "ProfileChanger onUpdate!");
        auto& ProfileChanger = ProfileChanger::getInstance();

        util::log(M_Debug, "enabledUid: %d", ProfileChanger.f_EnabledUid.getValue());

        __try {
            if (ProfileChanger.f_EnabledUid.getValue()) 
                Change_UID(Uid_buf);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            util::log(M_Error, "Exception 0x%08x.", _exception_code());
        }

        CALL_ORIGIN(onUpdate_1, __this);
    }

    static void InstallHooks() {
        HookManager::install(app::GameManager_Update2, onUpdate_1);
    }
}
