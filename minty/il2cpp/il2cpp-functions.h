#include "il2cpp-types.h"

using namespace app;

// Cooldown cheats
DO_APP_FUNC(0x00E599B0, 0x0, void, MoleMole_LCVehicleCombat_UpdateSkillCD, (void* __this, uint32_t skillID, uint32_t cd));
DO_APP_FUNC(0x03FB80E0, 0x03FC3090, bool, MoleMole_HumanoidMoveFSM_CheckSprintCooldown, (/* HumanoidMoveFSM */void* __this));
DO_APP_FUNC(0x03004A80, 0x0300FB20, bool, MoleMole_LCAvatarCombat_IsEnergyMax, (void* __this));
DO_APP_FUNC(0x0300ABE0, 0x03015C50, bool, MoleMole_LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float multipler));
DO_APP_FUNC(0x02FD17D0, 0x02FDC9A0, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));

// Visuals
DO_APP_FUNC(0x0253E130, 0x02546640, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data));
DO_APP_FUNC(0x00C35920, 0x00C3A420, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (app::MoleMole_VCBaseSetDitherValue* __this, float value));

// God mode
DO_APP_FUNC(0x02123990, 0x0212B830, void, VCHumanoidMove_NotifyLandVelocity, (app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0x02DB2A60, 0x02DBD750, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attacker, app::BaseEntity* target, bool checkBackstage));
DO_APP_FUNC(0x02749300, 0x02751BE0, void, MoleMole_LCBaseCombat_FireBeingHitEvent, (app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult));
DO_APP_FUNC(0x02FA6AF0, 0x02FB1C90, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (app::ActorAbilityPlugin* __this, float delay, app::Object* arg));

// Utility
DO_APP_FUNC(0x0141BE70, 0x01421A80, app::Vector3, ActorUtils_GetAvatarPos, ());
DO_APP_FUNC(0x01408E20, 0x0140EA50, void, ActorUtils_SetAvatarPos, (app::Vector3 pos));

DO_APP_FUNC(0x06E62170, 0x06EA6530, void, Text_set_text, (app::Text* __this, app::String* value));
DO_APP_FUNC(0x06E61CF0, 0x06EA60B0, void, Text_set_alignment, (app::Text* __this, app::TextAnchor__Enum value));
DO_APP_FUNC(0x06E61F30, 0x06EA62F0, void, Text_set_horizontalOverflow, (app::Text* __this, app::HorizontalWrapMode__Enum value));
DO_APP_FUNC(0x06E62260, 0x06EA6620, void, Text_set_verticalOverflow, (app::Text* __this, app::VerticalWrapMode__Enum value));
DO_APP_FUNC(0x06E61FF0, 0x06EA63B0, void, Text_set_resizeTextForBestFit, (app::Text* __this, bool value));
DO_APP_FUNC(0x06E61DF0, 0x06EA6210, void, Text_set_fontSize, (app::Text* __this, int32_t value));

DO_APP_FUNC(0x06DC74C0, 0x06E0C2D0, void, Slider_1_set_minValue, (app::Slider_1* __this, float value));
DO_APP_FUNC(0x06DC7470, 0x06E0C280, void, Slider_1_set_maxValue, (app::Slider_1* __this, float value));
DO_APP_FUNC(0x06DC7550, 0x06E0C360, void, Slider_1_set_value, (app::Slider_1* __this, float value));

DO_APP_FUNC(0x06D6A310, 0x06DAF120, app::Vector3, Transform_get_right, (app::Transform* __this));
DO_APP_FUNC(0x06D6A3F0, 0x06DAF200, app::Vector3, Transform_get_up, (app::Transform* __this));
DO_APP_FUNC(0x06D6A040, 0x06DAEE50, app::Vector3, Transform_get_forward, (app::Transform* __this));

// should be 'op_Implicit' not 'get_value'
DO_APP_FUNC(0x02C101D0, 0x02C1A8E0, float, MoleMole_SafeFloat_get_Value, (app::SafeFloat safeFloat));
// should be 'op_Implicit' not 'set_value'
DO_APP_FUNC(0x02C10260, 0x02C1A970, app::SafeFloat, MoleMole_SafeFloat_set_Value, (float value));

DO_APP_FUNC(0x067EE040, 0x0682F680, app::String*, Marshal_PtrToStringAnsi, (void* ptr));

// Game Object, Transform, Object, Component Utility
DO_APP_FUNC(0x06E48A80, 0x06E8CF50, app::GameObject*, GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x06E48F80, 0x06E8D530, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x06E48E50, 0x06E8D320, void, GameObject_SetActive, (app::GameObject* __this, bool value));
DO_APP_FUNC(0x06E48AB0, 0x06E8CF80, app::GameObject*, GameObject_Find, (app::String* name));
DO_APP_FUNC(0x06E48AC0, 0x06E8CFE0, app::Component_1*, GameObject_GetComponentByName, (app::GameObject* __this, void* type));
DO_APP_FUNC(0x06E48A00, 0x06E8CED0, app::Component_1*, GameObject_AddComponentInternal, (app::GameObject* __this, app::String* className));
DO_APP_FUNC(0x06E49040, 0x06E8D510, app::Transform*, GameObject_get_transform, (app::GameObject* __this));

DO_APP_FUNC(0x06D68EC0, 0x06DADCD0, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x06D68EB0, 0x06DADCC0, int32_t, Transform_GetChildCount, (app::Transform* __this));
DO_APP_FUNC(0x06D6A620, 0x06DAF430, void, Transform_set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x06D690C0, 0x06DADE90, void, Transform_set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x06D6A1D0, 0x06DAEFE0, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x06D690D0, 0x06DADEA0, void, Transform_set_localScale, (app::Transform* __this, app::Vector3 value));

DO_APP_FUNC(0x06D65A10, 0x06DAA860, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x06D652D0, 0x06DAA120, void, Object_1_DestroyImmediate_1, (app::Object_1* obj));

DO_APP_FUNC(0x06D5DE40, 0x06DA2C30, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));

// UnityEngine
DO_APP_FUNC(0x06E15980, 0x06E59F70, void, RenderSettings_set_fog, (bool value));

DO_APP_FUNC(0x06E4B270, 0x06E8F830, float, Time_get_deltaTime, ());
DO_APP_FUNC(0x06E4B350, 0x06E8F910, float, Time_get_timeScale, ());
DO_APP_FUNC(0x06E4B400, 0x06E8F9C0, void*, Time_set_timeScale, (float time));

DO_APP_FUNC(0x06E39130, 0x06E7D740, bool*, Application_get_isFocused, ());
DO_APP_FUNC(0x06E397B0, 0x06E7DDC0, void*, Application_set_targetFrameRate, (int32_t value));

DO_APP_FUNC(0x06E7C1A0, 0x06EC0350, void*, QualitySettings_set_vSyncCount, (int32_t value));

DO_APP_FUNC(0x06E530F0, 0x06E97820, float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));
DO_APP_FUNC(0x06E53500, 0x06E97C50, app::Vector3, Vector3_Lerp, (app::Vector3 start, app::Vector3 end, float time));

DO_APP_FUNC(0x06D79560, 0x06DBDE00, bool, Cursor_get_visible, (app::MethodInfo* method));
DO_APP_FUNC(0x06D79580, 0x06DBDE20, void, Cursor_set_visible, (bool value));
DO_APP_FUNC(0x06D79570, 0x06DBDE10, void, Cursor_set_lockState, (app::CursorLockMode__Enum value));

DO_APP_FUNC(0x06D62D90, 0x06DA7B80, int32_t, Screen_get_width, (app::MethodInfo* method));
DO_APP_FUNC(0x06D62D20, 0x06DA7B10, int32_t, Screen_get_height, (app::MethodInfo* method));

DO_APP_FUNC(0x06D6A2D0, 0x06DAF0E0, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x06D6A6A0, 0x06DAF4B0, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x06D6A3A0, 0x06DAF1B0, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x06D690E0, 0x06DADEB0, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x06D6A2C0, 0x06DAF0D0, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x06D6A640, 0x06DAF450, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x06D69CC0, 0x06DAEAD0, void, Transform_Translate, (app::Transform* __this, app::Vector3 translation));

DO_APP_FUNC(0x06D06D50, 0x06D4C050, void, Rigidbody_set_velocity, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x06D06F80, 0x06D4BF80, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, app::CollisionDetectionMode__Enum value));
DO_APP_FUNC(0x06D06FA0, 0x06D4BFA0, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x06D06E40, 0x06D4BE40, app::Vector3, Rigidbody_get_position, (app::Rigidbody* __this));
DO_APP_FUNC(0x06D06D40, 0x06D4BD30, void, Rigidbody_set_position, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x06D06CB0, 0x06D4BCB0, void, Rigidbody_MovePosition, (app::Rigidbody* __this, app::Vector3 position));

DO_APP_FUNC(0x02DE7CF0, 0x06A7D740, void, Action_Invoke, (/*Action*/ void* __this));

// Lua functions
DO_APP_FUNC(0x022C5A40, 0x022CD8E0, void, MoleMole_LuaShellManager_ReportLuaShellResult, (void* __this, app::String* type, app::String* value));

// Free Camera
DO_APP_FUNC(0x06D96670, 0x06DDB1B0, void, Camera_set_fieldOfView, (app::Camera* __this, float value));

// World cheats
DO_APP_FUNC(0x0098B2A0, 0x0098F7A0, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0x0093A980, 0x0093F330, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));
DO_APP_FUNC(0x009398D0, 0x0093E210, void, MoleMole_LevelSceneElementViewPlugin_TriggerElementView, (app::LevelSceneElementViewPlugin* __this, bool trigger));

// Dialog skipping
DO_APP_FUNC(0x00A9B0E0, 0x00A9F580, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, app::Notify* notify));
DO_APP_FUNC(0x0416D8C0, 0x04178700, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x041707F0, 0x0417B630, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x0416CFC0, 0x04177E00, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));

// Skip Cutscene
DO_APP_FUNC(0x02590170, 0x02598750, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this, app::MethodInfo* method));
DO_APP_FUNC(0x02590030, 0x02598610, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this, app::MethodInfo* method));

// Chest Indicator
DO_APP_FUNC(0x02A12370, 0x02A1C560, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x02A130C0, 0x02A1D2B0, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x02A13DD0, 0x02A1DFC0, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));

// Profile Changer
DO_APP_FUNC(0x020E4DD0, 0x020ECC40, app::Button_1*, ProfilePage, (app::MonoInLevelPlayerProfilePage* __this, app::MethodInfo* method));

// Visuals
DO_APP_FUNC(0x0133A8C0, 0x01340300, void, MonoParticleDamageTextContainer_ShowDamageText, (void* __this, void* attackResult, void* attackee));
DO_APP_FUNC(0x0133AFC0, 0x01340A00, void, MonoParticleDamageTextContainer_ShowReactionText, (void* __this, void* reaction, void* elemType1, void* elemType2, void* attackee, int hitIndex));

// Modify
DO_APP_FUNC(0x03FBD750, 0x03FC8730, void, MoleMole_HumanoidMoveFSM_LateTick, (app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method));

// Entities
DO_APP_FUNC(0x0131F640, 0x0, app::MoleMole_EntityManager*, MoleMole_InLevelDrumPageContext_get_ENTITY, (app::MethodInfo* method));

DO_APP_FUNC(0x029EDB30, 0x0, app::BaseEntity*, MoleMole_EntityManager_GetLocalAvatarEntity, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x029F0270, 0x0, app::CameraEntity*, MoleMole_EntityManager_GetMainCameraEntity, (app::MoleMole_EntityManager* __this));
DO_APP_FUNC(0x029F2980, 0x0, app::BaseEntity*, MoleMole_EntityManager_GetValidEntity, (app::MoleMole_EntityManager* __this, uint32_t runtimeID));

DO_APP_FUNC(0x01114D90, 0x0, uint32_t, MoleMole_BaseEntity_get_runtimeID, (app::BaseEntity* __this));
DO_APP_FUNC(0x0111DD90, 0x0, uint32_t, MoleMole_BaseEntity_get_configID, (app::BaseEntity* __this));
DO_APP_FUNC(0x0111C030, 0x0, bool, MoleMole_BaseEntity_IsActive, (app::BaseEntity* __this));
DO_APP_FUNC(0x022D2940, 0x0, app::Animator*, MoleMole_BaseEntity_get_animator, (app::BaseEntity* __this));
DO_APP_FUNC(0x024C5010, 0x0, app::GameObject*, MoleMole_BaseEntity_get_rootGameObject, (app::BaseEntity* __this));
DO_APP_FUNC(0x0411F660, 0x0, app::Rigidbody*, MoleMole_BaseEntity_GetRigidbody, (app::BaseEntity* __this));
DO_APP_FUNC(0x01118BE0, 0x038104A0, app::EntityType__Enum_1, MoleMole_BaseEntity_get_entityType, (app::BaseEntity* __this));
DO_APP_FUNC(0x0412DF50, 0x0, app::Vector3, MoleMole_BaseEntity_GetRelativePosition, (app::BaseEntity* __this));
DO_APP_FUNC(0x0412CC20, 0x0, void, MoleMole_BaseEntity_SetRelativePosition, (app::BaseEntity* __this, app::Vector3 position, bool forceSyncToRigidbody));
DO_APP_FUNC(0x04118C30, 0x0, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));
DO_APP_FUNC(0x0412A8E0, 0x0, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));
DO_APP_FUNC(0x04122610, 0x0, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));

DO_APP_FUNC(0x02F20870, 0x0, app::BaseEntity*, MoleMole_GadgetEntity_GetOwnerEntity, (app::GadgetEntity* __this));

// Protection bypass
DO_APP_FUNC(0x03FEC590, 0x03FF74B0, app::Byte__Array*, MoleMole_SecurityModule_RecordUserData, (int32_t nType, app::MethodInfo* method));

// Skip enhance animation
DO_APP_FUNC(0x02828590, 0x02832AA0, void, MoleMole_EquipLevelUpDialogContext_SetupView, (app::MoleMole_EquipLevelUpDialogContext* __this));
DO_APP_FUNC(0x02826700, 0x02830C10, void, MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog, (/*MoleMole_EquipLevelUpDialogContext*/ void* __this));
DO_APP_FUNC(0x03985250, 0x0398FF90, void, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, (/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback));
DO_APP_FUNC(0x02D8E440, 0x02D99250, void, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, (/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction));

// Teleport hooks
DO_APP_FUNC(0x02262880, 0x0226AB70, void, GameManager_Update, (app::GameManager* __this, app::MethodInfo* method));

// Open team immediately
DO_APP_FUNC(0x04475550, 0x044816E0, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x00D82A70, 0x00D86F80, void, MoleMole_InLevelPlayerProfilePageContext_SetupView, (/*MoleMole_InLevelPlayerProfilePageContext*/ void* __this));
DO_APP_FUNC(0x00D7EFF0, 0x00D83500, void, MoleMole_InLevelPlayerProfilePageContext_ClearView, (/*MoleMole_InLevelPlayerProfilePageContext*/ void* __this));
DO_APP_FUNC(0x013E7B30, 0x013ED760, void, MoleMole_InLevelMainPageContext_EndCountDown, (app::InLevelMainPageContext* __this));

// Unlimited stamina
DO_APP_FUNC(0x03E693A0, 0x03E744C0, void, MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, (app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq));
DO_APP_FUNC(0x00B8B550, 0x0, app::MotionState__Enum, MotionInfo_get_State, (app::MotionInfo* __this));
DO_APP_FUNC(0x0341EBE0, 0x0, app::MotionState__Enum, MotionInfo_set_State, (app::MotionInfo* __this, app::MotionState__Enum value));
DO_APP_FUNC(0x01A04B70, 0x01A0B570, void, MoleMole_DataItem_HandleNormalProp, (app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state));
// Wanderer E Stamina
DO_APP_FUNC(0x02115EC0, 0x0211DD70, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));
