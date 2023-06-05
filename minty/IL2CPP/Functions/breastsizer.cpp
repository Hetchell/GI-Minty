#include "breastsizer.h"

static std::string ActiveHero;
static app::GameObject* pathBoob = new app::GameObject;
static app::GameObject* avatarBoobL;
static app::GameObject* avatarBoobR;

bool f_BoobL = false;
bool f_BoobR = false;

namespace il2fns {
    void ScaleBreast() {
        auto AvatarRoot = app::UnityEngine__GameObject__Find(string_to_il2cppi("/EntityRoot/AvatarRoot"));

        if (AvatarRoot != nullptr) {
            auto Transform = app::UnityEngine_GameObject_GetComponent(AvatarRoot, string_to_il2cppi("Transform"));
            auto HeroCount = app::UnityEngine_Transform_GetChildCount(reinterpret_cast<app::Transform*>(Transform));

            for (int i = 0; i <= HeroCount - 1; i++)
            {
                auto HeroComponent = app::Transform_GetChild(reinterpret_cast<app::Transform*>(Transform), i);
                auto HeroGameObject = app::Component_1_get_gameObject(reinterpret_cast<app::Component_1*>(HeroComponent));
                auto isActiveHero = app::GameObject_get_active(HeroGameObject);

                if (isActiveHero)
                {
                    auto GameObjectName = app::Object_1_get_name(reinterpret_cast<app::Object_1*>(HeroGameObject));
                    ActiveHero = il2cppi_to_string(GameObjectName);
                    std::string Hero = ActiveHero.erase(ActiveHero.find("(Clone)"));
                    util::log(M_Warning, "active hero is %s", ActiveHero.c_str());

                    std::string nameL = "/EntityRoot/AvatarRoot/" + il2cppi_to_string(GameObjectName) + "/OffsetDummy/" + Hero.c_str() + "/Bip001/Bip001 Pelvis/Bip001 Spine/Bip001 Spine1/Bip001 Spine2/+Breast L A01";
                    std::string nameR = "/EntityRoot/AvatarRoot/" + il2cppi_to_string(GameObjectName) + "/OffsetDummy/" + Hero.c_str() + "/Bip001/Bip001 Pelvis/Bip001 Spine/Bip001 Spine1/Bip001 Spine2/+Breast R A01";

                    auto GameObjectBreastL = app::UnityEngine__GameObject__Find(string_to_il2cppi(nameL.c_str()));
                    auto GameObjectBreastR = app::UnityEngine__GameObject__Find(string_to_il2cppi(nameR.c_str()));
                    if (app::GameObject_get_active(GameObjectBreastL) && app::GameObject_get_active(GameObjectBreastR))
                    {
                        avatarBoobL = GameObjectBreastL;
                        avatarBoobR = GameObjectBreastR;

                        auto transform_L = app::UnityEngine__Component__get__Transform(avatarBoobL);
                        auto transform_R = app::UnityEngine__Component__get__Transform(avatarBoobR);

                        auto parent_L = app::Transform_get_parent(transform_L);
                        auto parent_R = app::Transform_get_parent(transform_R);

                        auto localScale_L = app::Transform_get_localScale(transform_L);
                        auto localScale_R = app::Transform_get_localScale(transform_R);
                        app::set_localScale(transform_L, app::Vector3{ 10, 10, 10 });
                        app::set_localScale(transform_R, app::Vector3{ 10, 10, 10 });

                        auto rotation_L = app::Transform_get_rotation(transform_L);
                        auto rotation_R = app::Transform_get_rotation(transform_R);

                        auto position_L = app::Transform_get_position(transform_L);
                        auto position_R = app::Transform_get_position(transform_R);

                        if (!f_BoobL && !f_BoobR) {
                            app::GameObject__ctor(pathBoob, string_to_il2cppi("Boobs"));
                            auto obj_pathBoob = app::UnityEngine__GameObject__Find(string_to_il2cppi("Boobs"));
                            if (obj_pathBoob != nullptr)
                            {
                                auto transform_pathBoob = app::UnityEngine__Component__get__Transform(pathBoob);
                                app::Transform_set_parent(transform_pathBoob, parent_L);
                                app::set_localScale(transform_pathBoob, localScale_L);
                                app::Transform_set_rotation(transform_pathBoob, rotation_L);
                                app::Transform_set_position(transform_pathBoob, position_L);

                                app::Transform_set_parent(parent_L, transform_pathBoob);
                                app::Transform_set_parent(parent_R, transform_pathBoob);

                                app::Transform_set_parent(transform_L, transform_pathBoob); //Breast to Boobs
                                app::Transform_set_parent(transform_R, transform_pathBoob); //Breast to Boobs

                                app::set_localScale(transform_L, app::Vector3{ 10, 10, 10 });
                                app::set_localScale(transform_R, app::Vector3{ 10, 10, 10 });
                            }
                            f_BoobL, f_BoobR = true;
                        }
                    }
                }
            }
        }
        else {
            f_BoobL = false;
            f_BoobR = false;
        }
    }
}