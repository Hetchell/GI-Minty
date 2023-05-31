#include "il2cpp-types.h"
using namespace app;

DO_APP_FUNC(0x0363F220, void*, MoleMole__ActorUtils__ShowMessage, (void* message));
DO_APP_FUNC(0x00CABB60, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x3633B20, app::Vector3, MoleMole__ActorUtils__GetAvatarPos, ());
DO_APP_FUNC(0x707C250, void*, UnityEngine__set__Timescale, (float time));
DO_APP_FUNC(0x7040740, bool*, UnityEngine__Application__get__isFocused, ());
DO_APP_FUNC(0x7040C50, void*, UnityEngine__Application__set__targetFramerate, (int32_t value));
DO_APP_FUNC(0x7082720, void*, UnityEngine__QualitySettings__set__vSyncCount, (int32_t value));
DO_APP_FUNC(0x6F73BA0, void*, UnityEngine__Transform__set__localScale, (app::Transform* transformComponent, app::Vector3 vectorScale));
DO_APP_FUNC(0x8BFE60, app::Transform*, UnityEngine__Component__get__Transform, (app::GameObject* object));
DO_APP_FUNC(0x7079CA0, app::GameObject*, UnityEngine__GameObject__Find, (app::String* nameFind));
DO_APP_FUNC(0x707A050, void, UnityEngine__GameObject__SetActive, (app::GameObject* object, bool value));
DO_APP_FUNC(0x1C5DC00, bool, LCAvatarCombat_IsEnergyMax, (void* __this)); // -- checl!!!!!!!!!!
DO_APP_FUNC(0x1C604A0, bool, LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float cdmulti));
DO_APP_FUNC(0x2D00460, float, MoleMole_SafeFloat_get_Value, (SafeFloat safeFloat)); //found with op implicit
DO_APP_FUNC(0x2D003C0, SafeFloat, MoleMole_SafeFloat_set_Value, (float safeFloat)); // same
DO_APP_FUNC(0x1C61220, bool, MoleMole_LCAvatarCombat_IsSkillInCD_1, (LCAvatarCombat* __this, LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo));
DO_APP_FUNC(0x7079D10, app::Component_1*, UnityEngine_GameObject_GetComponent, (app::GameObject* __this, void* type));
DO_APP_FUNC(0x7053CB0, void, UnityEngine_Text_setText, (app::Text* __this, void* value));
DO_APP_FUNC(0x23A2BA0, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (MoleMole_VCBaseSetDitherValue* __this, float value));
DO_APP_FUNC(0x4223CA0, void, MoleMole_DataItem_HandleNormalProp, (DataItem* __this, uint32_t type, int64_t value, DataPropOp__Enum state));
DO_APP_FUNC(0x6F739D0, app::Transform*, UnityEngine_Transform_GetChild, (Transform* __this, int32_t index));
DO_APP_FUNC(0x6F739C0, int32_t, UnityEngine_Transform_GetChildCount, (Transform* __this));
DO_APP_FUNC(0x1D36AF0, void, VCHumanoidMove_NotifyLandVelocity, (VCHumanoidMove* __this, Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0xEEFFE0, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (ActorAbilityPlugin* __this, float delay, Object* arg));
DO_APP_FUNC(0x707A180, bool, UnityEngine_GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x7079C70, app::GameObject*, UnityEngine_GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x56D9C80, app::Vector3, GetRelativePosition, (app::Vector3 __this));
DO_APP_FUNC(0x6F75140, void, set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x6F73BA0, void, set_localScale, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x6F73B90, void, set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x7079C00, app::Component_1*, AddComponentInternal, (GameObject* __this, app::String* className));
DO_APP_FUNC(0x6F6FE60, void, Object_1_DestroyImmediate_1, (app::Object_1* obj)); // -- check another one rva!!!
DO_APP_FUNC(0x6F5C090, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));
DO_APP_FUNC(0x6F739D0, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x707A180, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x6F74DE0, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x6F74CF0, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x6F705B0, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x6F74EC0, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x6F74DF0, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x6F75160, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x6F75230, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x6F73BB0, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x707A130, void, GameObject__ctor, (app::GameObject* __this, void* name));
DO_APP_FUNC(0x10B7130, void, Camera_set_fieldOfView, (app::Camera* __this, float value));
DO_APP_FUNC(0x1D37B80, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));
DO_APP_FUNC(0x2D94270, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0xEFAF40, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));
DO_APP_FUNC(0x1EC6590, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x1EC7450, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x1EC80E0, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x12EC630, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x12E99E0, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x36F89D0, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x36F8890, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x12E9B70, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));
/* not tested
0x3CB8210 ! 
0x3CB93F0 
*/
DO_APP_FUNC(0x3CB93F0, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, Notify* notify));
DO_APP_FUNC(0x30FD0B0, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x31FCA30, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (SCameraModuleInitialize* __this, double deltaTime, CameraShareData* data));
DO_APP_FUNC(0x07A11690, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x07A11670, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, CollisionDetectionMode__Enum value));
DO_APP_FUNC(0x07AAF810, void, Transform_Translate, (app::Transform* __this, app::Vector3));
DO_APP_FUNC(0x041956C0, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));
DO_APP_FUNC(0x04173F80, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));
DO_APP_FUNC(0x01EC83D0, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));
DO_APP_FUNC(0x01EACE10, app::Vector3, MoleMole_BaseEntity_GetRelativePosition, (app::BaseEntity* __this));
DO_APP_FUNC(0x07B813B0, float, Time_get_deltaTime, ());
DO_APP_FUNC(0x2281F30, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));
DO_APP_FUNC(0x6970110, String*, Marshal_PtrToStringAnsi, (void* ptr));
DO_APP_FUNC(0x40350C0, app::BaseEntity*, MoleMole_EntityManager_GetLocalAvatarEntity, (app::MoleMole_EntityManager* __this)); // - not yet
DO_APP_FUNC(0x2191C0, void*, Singleton_GetInstance, (app::MethodInfo* method)); //idr
DO_APP_FUNC(0x388BF70, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attackerEntity, app::BaseEntity* targetEntity, bool idk));

DO_APP_FUNC_METHODINFO(0x09E89398, Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo); // - not yet

DO_APP_FUNC(0x43C80F0, app::EntityType__Enum_1, get_entityType, (app::BaseEntity* ent));


//DO_TYPEDEF(0x00000, Int32);