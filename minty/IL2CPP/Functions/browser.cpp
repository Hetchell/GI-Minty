#include "browser.h"

void CreateBrowser(float planeWidth, float planeHeight, std::string url, bool value) {
    app::GameObject* planeObject = nullptr;
    app::Component_1* BrowserComponents = nullptr;
    if (value) {
        auto entityRoot = app::UnityEngine__GameObject__Find(il2cpp_string_new("EntityRoot/AvatarRoot/"));
        if (!app::UnityEngine_GameObject_get_active(entityRoot))
            return;

        auto PrimitiveType = app::PrimitiveType__Enum::Plane;
        planeObject = app::UnityEngine_GameObject_CreatePrimitive(PrimitiveType);
        app::Transform* planeObject_Transform = app::UnityEngine__Component__get__Transform(planeObject);
        app::Quaternion planeObject_Transform_Quaternion = { 0.5, 0.5, -0.5, 0.5 };
        auto avatarPos = app::MoleMole__ActorUtils__GetAvatarPos();
        auto relativePos = app::GetRelativePosition(avatarPos);
        app::Vector3 planeObject_Transform_Vector3 = { relativePos.x, relativePos.y + 3, relativePos.z };
        app::Vector3 planeObject_Transform_Scale = { (1920 / 1000 * planeWidth), 1, (1080 / 1000 * planeHeight) };

        app::set_localPosition(planeObject_Transform, planeObject_Transform_Vector3);
        app::set_localScale(planeObject_Transform, planeObject_Transform_Scale);
        app::set_localRotation(planeObject_Transform, planeObject_Transform_Quaternion);

        std::string custom_url = url;
        BrowserComponents = app::AddComponentInternal(planeObject, il2cpp_string_new("Browser"));
        reinterpret_cast<app::Browser*>(BrowserComponents)->fields._url = il2cpp_string_new(custom_url.c_str());
        reinterpret_cast<app::Browser*>(BrowserComponents)->fields._width = 1920;
        reinterpret_cast<app::Browser*>(BrowserComponents)->fields._height = 1080;
        reinterpret_cast<app::Browser*>(BrowserComponents)->fields.forceNextRender = true;
        reinterpret_cast<app::Browser*>(BrowserComponents)->fields._EnableInput_k__BackingField = true;
    }
    else {
        app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(planeObject));
        app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(BrowserComponents));
        planeObject = nullptr;
        BrowserComponents = nullptr;
    }
}

//if (planeObject != nullptr && BrowserComponents != nullptr) {
//    app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(planeObject), nullptr);
//    app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(BrowserComponents), nullptr);
//    planeObject = nullptr;
//    BrowserComponents = nullptr;
//}

namespace il2fns {
	void TurnBrowser(bool value, float scale, std::string url) {
        if (value)
            CreateBrowser(scale, scale, url, true);
		else
            CreateBrowser(scale, scale, url, false);
	}
}