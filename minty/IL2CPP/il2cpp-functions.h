#include "il2cpp-types.h"
using namespace app;

// no sprint cd
DO_APP_FUNC(0x02E65370, bool, MoleMole_HumanoidMoveFSM_CheckSprintCooldown, (/* HumanoidMoveFSM */void* __this));
DO_APP_FUNC(0x02D2AFE0, void*, MoleMole__ActorUtils__ShowMessage, (void* message));
DO_APP_FUNC(0x02D1FF00, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x02D17590, app::Vector3, MoleMole__ActorUtils__GetAvatarPos, ());
DO_APP_FUNC(0x081B14A0, void*, UnityEngine__set__Timescale, (float time));
DO_APP_FUNC(0x0818D960, bool*, UnityEngine__Application__get__isFocused, ());
DO_APP_FUNC(0x0818D680, void*, UnityEngine__Application__set__targetFramerate, (int32_t value));
DO_APP_FUNC(0x081D96A0, void*, UnityEngine__QualitySettings__set__vSyncCount, (int32_t value));
DO_APP_FUNC(0x080BF900, void*, UnityEngine__Transform__set__localScale, (app::Transform* transformComponent, app::Vector3 vectorScale));
DO_APP_FUNC(0x081AF240, app::Transform*, UnityEngine__Component__get__Transform, (app::GameObject* object));
DO_APP_FUNC(0x081AF280, app::GameObject*, UnityEngine__GameObject__Find, (app::String* nameFind));
DO_APP_FUNC(0x081AF120, void, UnityEngine__GameObject__SetActive, (app::GameObject* object, bool value));
DO_APP_FUNC(0x017D01C0, bool, LCAvatarCombat_IsEnergyMax, (void* __this));
DO_APP_FUNC(0x017CC000, bool, LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float cdmulti));
DO_APP_FUNC(0x034D3980, float, MoleMole_SafeFloat_get_Value, (SafeFloat safeFloat));
DO_APP_FUNC(0x034D3AB0, SafeFloat, MoleMole_SafeFloat_set_Value, (float safeFloat));
DO_APP_FUNC(0x017D46E0, bool, MoleMole_LCAvatarCombat_IsSkillInCD_1, (LCAvatarCombat* __this, LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo));
DO_APP_FUNC(0x081AECA0, app::Component_1*, UnityEngine_GameObject_GetComponent, (app::GameObject* __this, void* type));
// set_text
DO_APP_FUNC(0x081BB7F0, void, UnityEngine_Text_setText, (app::Text* __this, void* value));
DO_APP_FUNC(0x02094C40, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (MoleMole_VCBaseSetDitherValue* __this, float value));
// wtf, need update args xd
DO_APP_FUNC(0x02242400, void, MoleMole_DataItem_HandleNormalProp, (DataItem* __this, uint32_t type, int64_t value, DataPropOp__Enum state));
DO_APP_FUNC(0x080BF390, app::Transform*, UnityEngine_Transform_GetChild, (Transform* __this, int32_t index));
DO_APP_FUNC(0x080BF880, int32_t, UnityEngine_Transform_GetChildCount, (Transform* __this));
DO_APP_FUNC(0x026C69B0, void, VCHumanoidMove_NotifyLandVelocity, (VCHumanoidMove* __this, Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0x03FD4340, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (ActorAbilityPlugin* __this, float delay, Object* arg));
DO_APP_FUNC(0x081AF010, bool, UnityEngine_GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x081AF030, app::GameObject*, UnityEngine_GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
// 0x06D09730
DO_APP_FUNC(0x06D095E0, app::Vector3, GetRelativePosition, (app::Vector3 __this));
DO_APP_FUNC(0x080BF8E0, void, set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BF900, void, set_localScale, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BF8F0, void, set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x081AEF70, app::Component_1*, AddComponentInternal, (GameObject* __this, app::String* className));
DO_APP_FUNC(0x080BA410, void, Object_1_DestroyImmediate_1, (app::Object_1* obj));
DO_APP_FUNC(0x080B0AB0, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));
DO_APP_FUNC(0x080BF390, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x081AF010, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x080BF580, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x080BE330, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x080BA230, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x080BE370, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x080BE360, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x080BF910, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x080BF9F0, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x080BE390, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x081AF050, void, GameObject__ctor, (app::GameObject* __this, void* name));
DO_APP_FUNC(0x080EE940, void, Camera_set_fieldOfView, (app::Camera* __this, float value));
DO_APP_FUNC(0x026C8D30, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));
DO_APP_FUNC(0x02FABDC0, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0x01B06350, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));
DO_APP_FUNC(0x03199A80, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x03197C80, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x031993D0, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x0407C6B0, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x0407A750, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x04636CD0, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x04636280, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x04079C40, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));

// No Clip
DO_APP_FUNC(0x02E5B050, void, MoleMole_HumanoidMoveFSM_LateTick, (app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method));
DO_APP_FUNC(0x081A9180, float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));
DO_APP_FUNC(0x080320B0, void, Rigidbody_set_position, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x08032000, void, Rigidbody_MovePosition, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x08032390, void, Rigidbody_set_velocity, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x081B1510, float, Time_get_deltaTime, ());
DO_APP_FUNC(0x08032050, app::Vector3, Rigidbody_get_position, (app::Rigidbody* __this));
DO_APP_FUNC(0x080BF660, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));
DO_APP_FUNC(0x080BF6B0, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));
DO_APP_FUNC(0x080BF300, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));
DO_APP_FUNC(0x080320B0, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x08031F90, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, app::CollisionDetectionMode__Enum value));
// idk, lmao, ahah, xddd
DO_APP_FUNC(0x10EF960, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, app::Notify* notify));
// duplicate
//DO_APP_FUNC(0x30FD0B0, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x0461E4C0, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data));
DO_APP_FUNC(0x080BEFB0, void, Transform_Translate, (app::Transform* __this, app::Vector3));
// very old? not used? yeap xdd
DO_APP_FUNC(0x01EACE10, app::Vector3, MoleMole_BaseEntity_GetRelativePosition, (app::BaseEntity* __this));
DO_APP_FUNC(0x03FDB3D0, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));
DO_APP_FUNC(0x07B15200, app::String*, Marshal_PtrToStringAnsi, (void* ptr));
DO_APP_FUNC(0x0475FA50, app::BaseEntity*, MoleMole_EntityManager_GetLocalAvatarEntity, (app::MoleMole_EntityManager* __this));
//idr
DO_APP_FUNC(0x2191C0, void*, Singleton_GetInstance, (app::MethodInfo* method));
DO_APP_FUNC(0x0484ED30, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attackerEntity, app::BaseEntity* targetEntity, bool idk));

// - not yet
//DO_APP_FUNC_METHODINFO(0x09E89398, Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo);

DO_APP_FUNC(0x0701B730, app::EntityType__Enum_1, get_entityType, (app::BaseEntity* ent));
DO_APP_FUNC(0x038BD390, void, MoleMole_LCBaseCombat_FireBeingHitEvent, (app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult));
DO_APP_FUNC(0x0816C090, void, RenderSettings_set_fog, (bool value));
DO_APP_FUNC(0x0818D2E0, app::Byte__Array*, Application_RecordUserData, (int32_t nType, app::MethodInfo* method));

// Skip enhance animation
DO_APP_FUNC(0x0320F780, void, MoleMole_EquipLevelUpDialogContext_SetupView, (app::MoleMole_EquipLevelUpDialogContext* __this));
DO_APP_FUNC(0x0320F590, void, MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog, (/*MoleMole_EquipLevelUpDialogContext*/ void* __this));
DO_APP_FUNC(0x03265A90, void, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, (/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback));
DO_APP_FUNC(0x0480B360, void, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, (/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction));

DO_APP_FUNC(0x07B914E0, void, Action_Invoke, (/*Action*/ void* __this));

// Teleport hooks
DO_APP_FUNC(0x00F9B100, void, GameManager_Update, (app::GameManager* __this, app::MethodInfo* method));

// Open team immediately
DO_APP_FUNC(0x02B963D0, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x0131DF00, void, MoleMole_InLevelPlayerProfilePageContext_SetupView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));
DO_APP_FUNC(0x0131BB50, void, MoleMole_InLevelPlayerProfilePageContext_ClearView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));

DO_APP_FUNC(0x03D27C70, void, MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, (app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t HAOCOEMOMBG));
