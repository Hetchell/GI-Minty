#include "il2cpp-types.h"
using namespace app;

// Cooldown cheats
DO_APP_FUNC(0x02E63F50, 0x02EA09F0, bool, MoleMole_HumanoidMoveFSM_CheckSprintCooldown, (/* HumanoidMoveFSM */void* __this));
DO_APP_FUNC(0x017D4490, 0x017EC200, bool, LCAvatarCombat_IsEnergyMax, (void* __this));
DO_APP_FUNC(0x017CE2F0, 0x017E5E30, bool, LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float cdmulti));
DO_APP_FUNC(0x017D2D90, 0x017EAA80, bool, MoleMole_LCAvatarCombat_IsSkillInCD_1, (LCAvatarCombat* __this, LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo));
DO_APP_FUNC(0x03FB79A0, 0x04013D60, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));

// Visuals
DO_APP_FUNC(0x04623B60, 0x04689C30, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data));
DO_APP_FUNC(0x02091360, 0x020B6090, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (app::MoleMole_VCBaseSetDitherValue* __this, float value));

// God mode
DO_APP_FUNC(0x026D40E0, 0x027032A0, void, VCHumanoidMove_NotifyLandVelocity, (app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0x048346B0, 0x0489D100, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attackerEntity, app::BaseEntity* targetEntity, bool idk));
DO_APP_FUNC(0x038BD1E0, 0x0390F140, void, MoleMole_LCBaseCombat_FireBeingHitEvent, (app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult));
DO_APP_FUNC(0x03FD5F00, 0x04032990, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (app::ActorAbilityPlugin* __this, float delay, Object* arg));

// Utility
DO_APP_FUNC(0x02D1FA80, 0x02D586B0, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x02D2E3A0, 0x02D67B60, void*, MoleMole__ActorUtils__ShowMessage, (void* message));
DO_APP_FUNC(0x02D222A0, 0x02D5AFD0, app::Vector3, MoleMole__ActorUtils__GetAvatarPos, ());
// set_text
DO_APP_FUNC(0x081BC5E0, 0x08200750, void, UnityEngine_Text_setText, (app::Text* __this, void* value));
DO_APP_FUNC(0x06D0A9E0, 0x06D5E2B0, app::Vector3, GetRelativePosition, (app::Vector3 __this));
//DO_APP_FUNC(0x01EACE10, app::Vector3, MoleMole_BaseEntity_GetRelativePosition, (app::BaseEntity* __this));
//DO_APP_FUNC(0x0475D250, app::BaseEntity*, MoleMole_EntityManager_GetLocalAvatarEntity, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x080BFBD0, 0x08104250, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));
DO_APP_FUNC(0x080BFCB0, 0x08104330, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));
DO_APP_FUNC(0x080BF900, 0x08103F80, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));

// should be 'op_Implicit' not 'get_value'
DO_APP_FUNC(0x034D44E0, 0x0351D380, float, MoleMole_SafeFloat_get_Value, (app::SafeFloat safeFloat));
// should be 'op_Implicit' not 'set_value'
DO_APP_FUNC(0x034D4570, 0x0351D410, app::SafeFloat, MoleMole_SafeFloat_set_Value, (float safeFloat));

DO_APP_FUNC(0x04A77B90, 0x04491B00, app::EntityType__Enum_1, get_entityType, (app::BaseEntity* ent));
DO_APP_FUNC(0x07B15400, 0x07B5CB50, app::String*, Marshal_PtrToStringAnsi, (void* ptr));

// Game Object, Component, Transform Utility
DO_APP_FUNC(0x081AF090, 0x081F3650, void, GameObject__ctor, (app::GameObject* __this, void* name));
DO_APP_FUNC(0x081AEBE0, 0x081F31A0, app::GameObject*, UnityEngine_GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x081AF0E0, 0x081F36A0, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x081AEFB0, 0x081F3570, void, UnityEngine__GameObject__SetActive, (app::GameObject* object, bool value));
DO_APP_FUNC(0x081AEC10, 0x081F31D0, app::GameObject*, UnityEngine__GameObject__Find, (app::String* nameFind));
DO_APP_FUNC(0x081AEC70, 0x081F31E0, app::Component_1*, UnityEngine_GameObject_GetComponent, (app::GameObject* __this, void* type));
DO_APP_FUNC(0x081AEB60, 0x081F3120, app::Component_1*, AddComponentInternal, (app::GameObject* __this, app::String* className));
DO_APP_FUNC(0x081AF190, 0x081F3750, app::Transform*, UnityEngine__Component__get__Transform, (app::GameObject* object));
DO_APP_FUNC(0x080BE7A0, 0x08102E10, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x080BE790, 0x08102E00, int32_t, UnityEngine_Transform_GetChildCount, (app::Transform* __this));
DO_APP_FUNC(0x080BFEE0, 0x08104560, void, set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BFEF0, 0x08102FF0, void, set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x080BFA90, 0x08104110, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x080BFF00, 0x08103000, void, set_localScale, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BAF00, 0x080FF580, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x080BA7C0, 0x080FEE30, void, Object_1_DestroyImmediate_1, (app::Object_1* obj));
DO_APP_FUNC(0x080B1380, 0x080F59E0, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));

// UnityEngine
DO_APP_FUNC(0x0816BD50, 0x081B0870, void, RenderSettings_set_fog, (bool value));
DO_APP_FUNC(0x081B1090, 0x081F56E0, float, Time_get_deltaTime, ());
DO_APP_FUNC(0x081B1220, 0x081F5870, void*, UnityEngine__set__Timescale, (float time));

DO_APP_FUNC(0x0818D790, 0x081D22B0, bool*, UnityEngine__Application__get__isFocused, ());
DO_APP_FUNC(0x0818DD90, 0x081D28A0, void*, UnityEngine__Application__set__targetFramerate, (int32_t value));
DO_APP_FUNC(0x081D9B50, 0x0821DF10, void*, UnityEngine__QualitySettings__set__vSyncCount, (int32_t value));

DO_APP_FUNC(0x081A8C10, 0x081ED310, float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));

DO_APP_FUNC(0x080DABD0, 0x0811F2A0, bool, Cursor_get_visible, (app::MethodInfo* method));
DO_APP_FUNC(0x080DABF0, 0x0811F2C0, void, Cursor_set_visible, (bool value));
DO_APP_FUNC(0x080DABE0, 0x0811F290, void, Cursor_set_lockState, (app::CursorLockMode__Enum value));

DO_APP_FUNC(0x080BFB90, 0x08104210, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x080BE990, 0x081045E0, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x080BFC60, 0x081042E0, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x080BFFF0, 0x08104660, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x080BFB80, 0x08104200, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x080BFF20, 0x08104580, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x080BF580, 0x08103C00, void, Transform_Translate, (app::Transform* __this, app::Vector3));

DO_APP_FUNC(0x08032C00, 0x08076CD0, void, Rigidbody_set_velocity, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x08032B40, 0x08076BF0, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, app::CollisionDetectionMode__Enum value));
DO_APP_FUNC(0x08032B60, 0x08076C10, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x08032A10, 0x08076AB0, app::Vector3, Rigidbody_get_position, (app::Rigidbody* __this));
DO_APP_FUNC(0x08032910, 0x08076C90, void, Rigidbody_set_position, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x08032930, 0x08076910, void, Rigidbody_MovePosition, (app::Rigidbody* __this, app::Vector3 value));

DO_APP_FUNC(0x07FD5E70, 0x05937000, void, Action_Invoke, (/*Action*/ void* __this));

// Free Camera
DO_APP_FUNC(0x080EE9E0, 0x081333E0, void, Camera_set_fieldOfView, (app::Camera* __this, float value));

// World cheats
DO_APP_FUNC(0x02FABC70, 0x02FEA740, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0x01B06C80, 0x01B228B0, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));

// Dialog skipping
DO_APP_FUNC(0x02F6E080, 0x02FACC10, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, app::Notify* notify));
DO_APP_FUNC(0x040D97E0, 0x040DA9D0, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x0407D0F0, 0x040DACB0, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x04079840, 0x040D7220, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));

// Skip Cutscene
DO_APP_FUNC(0x046376E0, 0x0469D6B0, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x046375A0, 0x0469D570, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this));

// Chest Indicator
DO_APP_FUNC(0x03198BD0, 0x031D8B50, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x03198D60, 0x031D8CE0, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x0319A1B0, 0x031DA120, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));

// Modify
DO_APP_FUNC(0x02E5F490, 0x02E9BEC0, void, MoleMole_HumanoidMoveFSM_LateTick, (app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method));

// Singletons
//idr
//DO_APP_FUNC(0x2191C0, 0x0, void*, Singleton_GetInstance, (app::MethodInfo* method));

// not yet
//DO_APP_FUNC_METHODINFO(0x09E89398, Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo);

// Protection bypass
DO_APP_FUNC(0x0818D110, 0x081D1C20, app::Byte__Array*, Application_RecordUserData, (int32_t nType, app::MethodInfo* method));

// Skip enhance animation
DO_APP_FUNC(0x032106E0, 0x03252210, void, MoleMole_EquipLevelUpDialogContext_SetupView, (app::MoleMole_EquipLevelUpDialogContext* __this));
DO_APP_FUNC(0x032102A0, 0x03251D80, void, MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog, (/*MoleMole_EquipLevelUpDialogContext*/ void* __this));
DO_APP_FUNC(0x032661F0, 0x032A87E0, void, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, (/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback));
DO_APP_FUNC(0x04807840, 0x0486FD90, void, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, (/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction));

// Teleport hooks
DO_APP_FUNC(0x00F9C200, 0x00FA54B0, void, GameManager_Update, (app::GameManager* __this, app::MethodInfo* method));

// Open team immediately
DO_APP_FUNC(0x02B95F60, 0x02BCBD60, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x01322CE0, 0x01332900, void, MoleMole_InLevelPlayerProfilePageContext_SetupView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));
DO_APP_FUNC(0x0131C600, 0x0132BE40, void, MoleMole_InLevelPlayerProfilePageContext_ClearView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));

// Unlimited stamina
DO_APP_FUNC(0x03D27FA0, 0x03D7F420, void, MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, (app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t HAOCOEMOMBG));
DO_APP_FUNC(0x02242760, 0x02268FB0, void, MoleMole_DataItem_HandleNormalProp, (app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state));
// Wanderer E Stamina
DO_APP_FUNC(0x026CD5D0, 0x026FC6C0, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));
