#include "ProfileChanger.h"

namespace cheat {
    static void onUpdate_1(app::GameManager* __this, app::MethodInfo* method);
    void Change_UID(const std::string uidText);
    app::Button_1* ProfilePage(app::MonoInLevelPlayerProfilePage* __this, app::MethodInfo* method);

    ProfileChanger::ProfileChanger(): Function() {
        f_EnabledUid = config::getValue("functions:ProfileChanger:UID", "enabled", false);
        f_UidValue = config::getValue<std::string>("functions:ProfileChanger:UID", "value", "");

        HookManager::install(app::GameManager_Update, onUpdate_1);
        HookManager::install(app::ProfilePage, ProfilePage);
    }

    ProfileChanger& ProfileChanger::getInstance() {
        static ProfileChanger instance;
        return instance;
    }

    void ProfileChanger::GUI() {
        ConfigCheckbox("Profile Changer", f_EnabledUid);

        if (f_EnabledUid.getValue()) {
            ImGui::Indent();
            ConfigInputText("Custom UID", f_UidValue);
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
    void Change_UID(const std::string uidText) {
        if (uidTextObj == nullptr)
            uidTextObj = app::UnityEngine__GameObject__Find(string_to_il2cppi("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"));

        if (uidTextObj != nullptr && uidTextComp == nullptr)
            uidTextComp = app::UnityEngine_GameObject_GetComponent(uidTextObj, string_to_il2cppi("Text"));

        app::UnityEngine_Text_setText(reinterpret_cast<app::Text*>(uidTextComp), string_to_il2cppi(uidText));
    }

    void onUpdate_1(app::GameManager* __this, app::MethodInfo* method) {
        auto& ProfileChanger = ProfileChanger::getInstance();
        std::string value = ProfileChanger.f_UidValue.getValue();

       if (ProfileChanger.f_EnabledUid.getValue())
           Change_UID(value.empty() ? "" : value);

        CALL_ORIGIN(onUpdate_1, __this, method);
    }


    app::Button_1* ProfilePage(app::MonoInLevelPlayerProfilePage* __this, app::MethodInfo* method) {
        auto& ProfileChanger = ProfileChanger::getInstance();

        if (ProfileChanger.f_EnabledUid.getValue()) {
            app::UnityEngine_Text_setText(__this->fields._playerID, string_to_il2cppi(ProfileChanger.f_UidValue.getValue()));
            //app::UnityEngine_Text_setText(__this->fields._playerLv, string_to_il2cppi(ProfileChanger.f_UidValue.getValue()));
            //app::UnityEngine_Text_setText(__this->fields._playerBirthday, string_to_il2cppi(ProfileChanger.f_UidValue.getValue()));
            //app::UnityEngine_Text_setText(__this->fields._playerName, string_to_il2cppi(ProfileChanger.f_UidValue.getValue()));
        }
        return CALL_ORIGIN(ProfilePage, __this, method);
    }
}
