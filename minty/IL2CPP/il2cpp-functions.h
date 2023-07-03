#include "il2cpp-types.h"
using namespace app;

DO_APP_FUNC(0x01E6D2E0, void*, MoleMole__ActorUtils__ShowMessage, (void* message));
DO_APP_FUNC(0x00CABB60, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x01E68E30, app::Vector3, MoleMole__ActorUtils__GetAvatarPos, ());
DO_APP_FUNC(0x07B32DC0, void*, UnityEngine__set__Timescale, (float time));
DO_APP_FUNC(0x07AFEA70, bool*, UnityEngine__Application__get__isFocused, ());
DO_APP_FUNC(0x07AFEF60, void*, UnityEngine__Application__set__targetFramerate, (int32_t value));
DO_APP_FUNC(0x07B3B010, void*, UnityEngine__QualitySettings__set__vSyncCount, (int32_t value));
DO_APP_FUNC(0x07A387A0, void*, UnityEngine__Transform__set__localScale, (app::Transform* transformComponent, app::Vector3 vectorScale));
DO_APP_FUNC(0x07A25F20, app::Transform*, UnityEngine__Component__get__Transform, (app::GameObject* object));
DO_APP_FUNC(0x07B30840, app::GameObject*, UnityEngine__GameObject__Find, (app::String* nameFind));
DO_APP_FUNC(0x07B30BE0, void, UnityEngine__GameObject__SetActive, (app::GameObject* object, bool value));
DO_APP_FUNC(0x1C5DC00, bool, LCAvatarCombat_IsEnergyMax, (void* __this)); // =
DO_APP_FUNC(0x1C604A0, bool, LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float cdmulti)); // =
DO_APP_FUNC(0x2D00460, float, MoleMole_SafeFloat_get_Value, (SafeFloat safeFloat)); //found with op implicit =
DO_APP_FUNC(0x2D003C0, SafeFloat, MoleMole_SafeFloat_set_Value, (float safeFloat)); // same =
DO_APP_FUNC(0x1C61220, bool, MoleMole_LCAvatarCombat_IsSkillInCD_1, (LCAvatarCombat* __this, LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo)); // =
DO_APP_FUNC(0x07B308B0, app::Component_1*, UnityEngine_GameObject_GetComponent, (app::GameObject* __this, void* type)); // 0x07B30850
DO_APP_FUNC(0x07B16AA0, void, UnityEngine_Text_setText, (app::Text* __this, void* value)); // set_text
DO_APP_FUNC(0x23A2BA0, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (MoleMole_VCBaseSetDitherValue* __this, float value)); // =
DO_APP_FUNC(0x4223CA0, void, MoleMole_DataItem_HandleNormalProp, (DataItem* __this, uint32_t type, int64_t value, DataPropOp__Enum state)); // =
DO_APP_FUNC(0x07A385A0, app::Transform*, UnityEngine_Transform_GetChild, (Transform* __this, int32_t index));
DO_APP_FUNC(0x07A38590, int32_t, UnityEngine_Transform_GetChildCount, (Transform* __this));
DO_APP_FUNC(0x1D36AF0, void, VCHumanoidMove_NotifyLandVelocity, (VCHumanoidMove* __this, Vector3 velocity, float reachMaxDownVelocityTime)); // =
DO_APP_FUNC(0xEEFFE0, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (ActorAbilityPlugin* __this, float delay, Object* arg)); // =
DO_APP_FUNC(0x07B30D10, bool, UnityEngine_GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x07B30810, app::GameObject*, UnityEngine_GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x05C1CF90, app::Vector3, GetRelativePosition, (app::Vector3 __this)); // 0x05C1D0C0
DO_APP_FUNC(0x07A38790, void, set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07A387A0, void, set_localScale, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07A39D10, void, set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x07B30790, app::Component_1*, AddComponentInternal, (GameObject* __this, app::String* className));
DO_APP_FUNC(0x07A34600, void, Object_1_DestroyImmediate_1, (app::Object_1* obj)); // 0x07A345F0
DO_APP_FUNC(0x07A25EE0, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));
DO_APP_FUNC(0x07A385A0, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x07B30D10, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x07A399B0, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x07A398C0, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x07A34D60, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x07A39A90, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x07A399C0, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x07A39D30, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x07A39E00, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x07A387B0, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07B30CC0, void, GameObject__ctor, (app::GameObject* __this, void* name)); // 0x07B30CA0 0x07B30C20
DO_APP_FUNC(0x07A60280, void, Camera_set_fieldOfView, (app::Camera* __this, float value));
DO_APP_FUNC(0x1D37B80, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value)); // =
DO_APP_FUNC(0x2D94270, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID)); // =

// 3.7 (check)
DO_APP_FUNC(0xEFAF40, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));
// 3.7 (check)
DO_APP_FUNC(0x1EC6590, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
// 3.7 (check)
DO_APP_FUNC(0x1EC7450, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
// 3.7 (check)
DO_APP_FUNC(0x1EC80E0, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));
// 3.7 (check)
DO_APP_FUNC(0x12EC630, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
// 3.7 (check)
DO_APP_FUNC(0x12E99E0, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x032D4E50, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x032D4D10, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this));
// 3.7 (check)
DO_APP_FUNC(0x12E9B70, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));

// No Clip
// 3.7 (check)
DO_APP_FUNC(0x15CAEA0, void, MoleMole_HumanoidMoveFSM_LateTick, (app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method));
DO_APP_FUNC(0x00D4D2D0, void, GameManager_Update, (app::GameManager* __this, app::MethodInfo* method));
DO_APP_FUNC(0x07B246F0, float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));
DO_APP_FUNC(0x079E4320, void, Rigidbody_set_position, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x079E3FA0, void, Rigidbody_MovePosition, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x079E4350, void, Rigidbody_set_velocity, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x07B32C30, float, Time_get_deltaTime, ());
DO_APP_FUNC(0x079E4150, app::Vector3, Rigidbody_get_position, (app::Rigidbody* __this));
DO_APP_FUNC(0x07A39730, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));
DO_APP_FUNC(0x07A39A00, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));
DO_APP_FUNC(0x07A39AE0, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));
DO_APP_FUNC(0x079E42A0, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x079E4280, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, app::CollisionDetectionMode__Enum value));

/*
0x3CB8210
0x3CB93F0
*/
// not used :cry: 3.7 (check?)
DO_APP_FUNC(0x3CB8210, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, Notify* notify));
// 3.7 (check)
DO_APP_FUNC(0x30FD0B0, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
// 3.7 (check)
DO_APP_FUNC(0x31FCA30, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (SCameraModuleInitialize* __this, double deltaTime, CameraShareData* data));
/*
0x07A393B0
0x07A394D0
0x07A393E0
0x07A39430
0x07A395A0
0x07A39480
*/
DO_APP_FUNC(0x07A393B0, void, Transform_Translate, (app::Transform* __this, app::Vector3));
// very old? not used?
DO_APP_FUNC(0x01EACE10, app::Vector3, MoleMole_BaseEntity_GetRelativePosition, (app::BaseEntity* __this));
// 3.7 (check)
DO_APP_FUNC(0x2281F30, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));
/*
0x07410B70
0x07410B60
*/
DO_APP_FUNC(0x07410B70, String*, Marshal_PtrToStringAnsi, (void* ptr));
// 3.7 (check)
DO_APP_FUNC(0x40350C0, BaseEntity*, MoleMole_EntityManager_GetLocalAvatarEntity, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x2191C0, void*, Singleton_GetInstance, (app::MethodInfo* method)); //idr
// 3.7 (check)
DO_APP_FUNC(0x388BF70, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attackerEntity, app::BaseEntity* targetEntity, bool idk));

DO_APP_FUNC_METHODINFO(0x09E89398, Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo); // - not yet

// 3.7 (check)
DO_APP_FUNC(0x43C80F0, app::EntityType__Enum_1, get_entityType, (app::BaseEntity* ent));
// 3.7 (check)
DO_APP_FUNC(0x23F9100, void, MoleMole_LCBaseCombat_FireBeingHitEvent, (app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult));

(0x07AEB020, void, RenderSettings_set_fog, (bool value));
DO_APP_FUNC(0x07AFE4E0, Byte__Array*, Application_RecordUserData, (int32_t nType, app::MethodInfo* method));
