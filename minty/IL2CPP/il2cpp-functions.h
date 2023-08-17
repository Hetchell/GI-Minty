#include "il2cpp-types.h"
using namespace app;

// Cooldown cheats
DO_APP_FUNC(0x02E642E0, bool, MoleMole_HumanoidMoveFSM_CheckSprintCooldown, (/* HumanoidMoveFSM */void* __this));
DO_APP_FUNC(0x017D46E0, bool, LCAvatarCombat_IsEnergyMax, (void* __this));
DO_APP_FUNC(0x017CE540, bool, LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float cdmulti));
DO_APP_FUNC(0x017D2FE0, bool, MoleMole_LCAvatarCombat_IsSkillInCD_1, (LCAvatarCombat* __this, LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo));
DO_APP_FUNC(0x03FB7160, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));

// Visuals
DO_APP_FUNC(0x046234E0, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data));
DO_APP_FUNC(0x02091930, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (app::MoleMole_VCBaseSetDitherValue* __this, float value));

// God mode
DO_APP_FUNC(0x026D5140, void, VCHumanoidMove_NotifyLandVelocity, (app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0x04833640, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attackerEntity, app::BaseEntity* targetEntity, bool idk));
DO_APP_FUNC(0x038BD280, void, MoleMole_LCBaseCombat_FireBeingHitEvent, (app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult));
DO_APP_FUNC(0x03FD56C0, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (app::ActorAbilityPlugin* __this, float delay, Object* arg));

// Utility
DO_APP_FUNC(0x02D2E550, void*, MoleMole__ActorUtils__ShowMessage, (void* message));
DO_APP_FUNC(0x02D1FC30, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x02D22450, app::Vector3, MoleMole__ActorUtils__GetAvatarPos, ());
// set_text
DO_APP_FUNC(0x081BC400, void, UnityEngine_Text_setText, (app::Text* __this, void* value));
DO_APP_FUNC(0x06D094B0, app::Vector3, GetRelativePosition, (app::Vector3 __this));
//DO_APP_FUNC(0x01EACE10, app::Vector3, MoleMole_BaseEntity_GetRelativePosition, (app::BaseEntity* __this));
//DO_APP_FUNC(0x0475D250, app::BaseEntity*, MoleMole_EntityManager_GetLocalAvatarEntity, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x080BF6B0, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));
DO_APP_FUNC(0x080BF300, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));
DO_APP_FUNC(0x080BF5D0, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));

// should be 'op_Implicit' not 'get_value'
DO_APP_FUNC(0x034D3F30, float, MoleMole_SafeFloat_get_Value, (app::SafeFloat safeFloat));
// should be 'op_Implicit' not 'set_value'
DO_APP_FUNC(0x034D3FC0, app::SafeFloat, MoleMole_SafeFloat_set_Value, (float safeFloat));

DO_APP_FUNC(0x04A76C90, app::EntityType__Enum_1, get_entityType, (app::BaseEntity* ent));
DO_APP_FUNC(0x07B151F0, app::String*, Marshal_PtrToStringAnsi, (void* ptr));

// Game Object, Component, Transform Utility
DO_APP_FUNC(0x081AF0F0, void, GameObject__ctor, (app::GameObject* __this, void* name));
DO_APP_FUNC(0x081AEC70, app::GameObject*, UnityEngine__GameObject__Find, (app::String* nameFind));
DO_APP_FUNC(0x081AF010, void, UnityEngine__GameObject__SetActive, (app::GameObject* object, bool value));
DO_APP_FUNC(0x081AF140, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x081AEC40, app::GameObject*, UnityEngine_GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x080BE1A0, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x080BE190, int32_t, UnityEngine_Transform_GetChildCount, (app::Transform* __this));
DO_APP_FUNC(0x080BF490, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x080BF8E0, void, set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BF8F0, void, set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x080BF900, void, set_localScale, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BA900, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x080BA1C0, void, Object_1_DestroyImmediate_1, (app::Object_1* obj));
DO_APP_FUNC(0x080B0D80, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));
DO_APP_FUNC(0x081AECD0, app::Component_1*, UnityEngine_GameObject_GetComponent, (app::GameObject* __this, void* type));
DO_APP_FUNC(0x081AEBC0, app::Component_1*, AddComponentInternal, (app::GameObject* __this, app::String* className));
DO_APP_FUNC(0x081AF1F0, app::Transform*, UnityEngine__Component__get__Transform, (app::GameObject* object));

// UnityEngine
DO_APP_FUNC(0x0816C0D0, void, RenderSettings_set_fog, (bool value));
DO_APP_FUNC(0x081B1570, void*, UnityEngine__set__Timescale, (float time));
DO_APP_FUNC(0x081B13E0, float, Time_get_deltaTime, ());

DO_APP_FUNC(0x0818D8D0, bool*, UnityEngine__Application__get__isFocused, ());
DO_APP_FUNC(0x0818DED0, void*, UnityEngine__Application__set__targetFramerate, (int32_t value));
DO_APP_FUNC(0x081D98E0, void*, UnityEngine__QualitySettings__set__vSyncCount, (int32_t value));

DO_APP_FUNC(0x081A8C80, float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));

DO_APP_FUNC(0x080BF590, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x080BE390, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BF660, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x080BF9F0, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x080BF580, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x080BF920, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x080BEF80, void, Transform_Translate, (app::Transform* __this, app::Vector3));

DO_APP_FUNC(0x080322D0, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, app::CollisionDetectionMode__Enum value));
DO_APP_FUNC(0x080322F0, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x080321A0, app::Vector3, Rigidbody_get_position, (app::Rigidbody* __this));
DO_APP_FUNC(0x080320B0, void, Rigidbody_set_position, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x08032390, void, Rigidbody_set_velocity, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x08032000, void, Rigidbody_MovePosition, (app::Rigidbody* __this, app::Vector3 value));

DO_APP_FUNC(0x077BDC80, void, Action_Invoke, (/*Action*/ void* __this));

// Free Camera
DO_APP_FUNC(0x080EE880, void, Camera_set_fieldOfView, (app::Camera* __this, float value));

// World cheats
DO_APP_FUNC(0x02FABDC0, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0x01B06C80, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));

// Dialog skipping
DO_APP_FUNC(0x02F6E460, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, app::Notify* notify));
DO_APP_FUNC(0x0407B870, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x0407CBF0, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x04079340, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));

// Skip Cutscene
DO_APP_FUNC(0x04636EA0, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x04636D60, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this));

// Chest Indicator
DO_APP_FUNC(0x03198060, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x031981F0, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x03199640, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));

// Modify
DO_APP_FUNC(0x02E5F820, void, MoleMole_HumanoidMoveFSM_LateTick, (app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method));

// Singletons
//idr
DO_APP_FUNC(0x2191C0, void*, Singleton_GetInstance, (app::MethodInfo* method));

// not yet
//DO_APP_FUNC_METHODINFO(0x09E89398, Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo);

// Protection bypass
DO_APP_FUNC(0x0818D250, app::Byte__Array*, Application_RecordUserData, (int32_t nType, app::MethodInfo* method));

// Skip enhance animation
DO_APP_FUNC(0x0320FBC0, void, MoleMole_EquipLevelUpDialogContext_SetupView, (app::MoleMole_EquipLevelUpDialogContext* __this));
DO_APP_FUNC(0x0320F780, void, MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog, (/*MoleMole_EquipLevelUpDialogContext*/ void* __this));
DO_APP_FUNC(0x03265DE0, void, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, (/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback));
DO_APP_FUNC(0x04806840, void, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, (/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction));

// Teleport hooks
DO_APP_FUNC(0x00F9BE80, void, GameManager_Update, (app::GameManager* __this, app::MethodInfo* method));

// Open team immediately
DO_APP_FUNC(0x02B96170, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x01323100, void, MoleMole_InLevelPlayerProfilePageContext_SetupView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));
DO_APP_FUNC(0x0131CA20, void, MoleMole_InLevelPlayerProfilePageContext_ClearView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));

// Unlimited stamina
DO_APP_FUNC(0x03D27AB0, void, MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, (app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t HAOCOEMOMBG));
DO_APP_FUNC(0x02243130, void, MoleMole_DataItem_HandleNormalProp, (DataItem* __this, uint32_t type, int64_t value, DataPropOp__Enum state));
// Wanderer E Stamina
DO_APP_FUNC(0x026CE630, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));
