#include "fakeconst.h"

void InitConstellations()
{
    for (auto& [_, talents] : m_AllTalents)
    {
        m_Talents.push_back({ config::CreateField<bool>(magic_enum::enum_name(talents.first).data(), "ConstellationModifier", false, false), talents.first });
    }
}

app::UInt32__Array* GetTalent(uint32_t avatarId)
{
    auto newArray = (app::UInt32__Array*)il2cpp_array_new((Il2CppClass*)*app::UInt32__TypeInfo, 6);
    auto talent = m_AllTalents.find(avatarId);
    if (talent == m_AllTalents.end())
        return newArray;
    if (std::any_of(m_Talents.begin(), m_Talents.end(), [&](std::pair<config::Field<bool>, Avatars>& info) {
        return talent->second.first == info.second && info.first;
        }))
        memmove_s(newArray->vector, 24, talent->second.second.data(), 24);
        return newArray;
}

void OnEntityAppear(app::Proto_SceneEntityAppearNotify* notify)
{
    auto entityList = notify->fields.entityList_;
    if (entityList == nullptr)
        return;
    for (int i = 0; i < entityList->fields.values->fields._size; i++)
    {
        auto& itemFields = entityList->fields.values->fields._items->vector[i]->fields;
        if (itemFields.entityCase_ == app::Proto_SceneEntityInfo_Proto_SceneEntityInfo_EntityOneofCase__Enum::Avatar)
        {
            auto avatar = CastTo<app::Proto_SceneAvatarInfo>(itemFields.entity_, *app::Proto_SceneAvatarInfo__TypeInfo);
            if (avatar != nullptr && GetTalent(avatar->fields.avatarId_)->vector[0] != 0)
            {
                avatar->fields.talentIdList_->fields.count = 6;
                avatar->fields.talentIdList_->fields._array = GetTalent(avatar->fields.avatarId_);
            }
        }
    }
}

namespace il2fns {
    void ModifyConst(bool value) {
        if (value) {
            InitConstellations();
            EntityAppearEvent += MY_METHOD_HANDLER(OnEntityAppear);
        }
    }
}