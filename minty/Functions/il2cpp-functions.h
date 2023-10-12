#include "il2cpp-types.h"

using namespace app;

DO_APP_FUNC(0x03C67F70, 0x03CDDBA0, void, ActorUtils_SetAvatarPos, (Vector3 pos));

// Cooldown cheats
DO_APP_FUNC(0x012FDB00, 0x01315C70, bool, MoleMole_HumanoidMoveFSM_CheckSprintCooldown, (/* HumanoidMoveFSM */void* __this));
DO_APP_FUNC(0x044CE4F0, 0x04555D40, bool, LCAvatarCombat_IsEnergyMax, (void* __this));
DO_APP_FUNC(0x044C7450, 0x0454EB20, bool, LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float cdmulti));
DO_APP_FUNC(0x044CB6E0, 0x04552E80, bool, MoleMole_LCAvatarCombat_IsSkillInCD_1, (app::LCAvatarCombat* __this, LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo));
DO_APP_FUNC(0x029B13B0, 0x02A02890, void, MoleMole_ActorAbilityPlugin_AddDynamicFloatWithRange, (app::MoleMole_ActorAbilityPlugin* __this, app::String* key, float value, float minf, float maxf, bool forceDoAtRemote));

// Visuals
DO_APP_FUNC(0x026C0250, 0x0270B1B0, void, MoleMole_SCameraModuleInitialize_SetWarningLocateRatio, (app::SCameraModuleInitialize* __this, double deltaTime, app::CameraShareData* data));
DO_APP_FUNC(0x031864D0, 0x031E5830, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (app::MoleMole_VCBaseSetDitherValue* __this, float value));

// God mode
DO_APP_FUNC(0x01C13E60, 0x01C43E10, void, VCHumanoidMove_NotifyLandVelocity, (app::VCHumanoidMove* __this, app::Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0x02043E70, 0x02080800, bool, Miscs_CheckTargetAttackable, (app::BaseEntity* attackerEntity, app::BaseEntity* targetEntity, bool idk));
DO_APP_FUNC(0x03D98130, 0x03E12370, void, MoleMole_LCBaseCombat_FireBeingHitEvent, (app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult));
DO_APP_FUNC(0x029A8090, 0x029F9460, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (app::ActorAbilityPlugin* __this, float delay, app::Object* arg));

// Utility
DO_APP_FUNC(0x0319A2C0, 0x031F9710, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x0319D7E0, 0x031FCE90, void*, MoleMole__ActorUtils__ShowMessage, (void* message));
DO_APP_FUNC(0x03C61C20, 0x03CEF350, app::Vector3, MoleMole__ActorUtils__GetAvatarPos, ());
// set_text
DO_APP_FUNC(0x07C08140, 0x07C96770, void, UnityEngine_Text_setText, (app::Text* __this, void* value));

DO_APP_FUNC(0x06102B40, 0x06191D30, app::Vector3, GetRelativePosition, (app::Vector3 __this));

DO_APP_FUNC(0x07AFF0F0, 0x07B8E640, app::Vector3, MoleMole_BaseEntity_GetRight, (app::BaseEntity* __this));
DO_APP_FUNC(0x07AFF1D0, 0x07B8E720, app::Vector3, MoleMole_BaseEntity_GetUp, (app::BaseEntity* __this));
DO_APP_FUNC(0x07AFEE20, 0x07B8E370, app::Vector3, MoleMole_BaseEntity_GetForward, (app::BaseEntity* __this));

// should be 'op_Implicit' not 'get_value'
DO_APP_FUNC(0x02DDE280, 0x02E36240, float, MoleMole_SafeFloat_get_Value, (app::SafeFloat safeFloat));
// should be 'op_Implicit' not 'set_value'
DO_APP_FUNC(0x02DDE1C0, 0x02E36180, app::SafeFloat, MoleMole_SafeFloat_set_Value, (float safeFloat));

DO_APP_FUNC(0x0150C6B0, 0x02AA34D0, app::EntityType__Enum_1, get_entityType, (app::BaseEntity* ent));

DO_APP_FUNC(0x07557AE0, 0x075E6D00, app::String*, Marshal_PtrToStringAnsi, (void* ptr));

// Game Object, Transform, Object, Component Utility
DO_APP_FUNC(0x07BFFC60, 0x07C8E3B0, void, GameObject__ctor, (app::GameObject* __this, void* name));
DO_APP_FUNC(0x07BFF830, 0x07C8DF70, app::GameObject*, UnityEngine_GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x07BFFD30, 0x07C8E480, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x07BFFC00, 0x07C8E350, void, UnityEngine__GameObject__SetActive, (app::GameObject* object, bool value));
DO_APP_FUNC(0x07BFF860, 0x07C8DFA0, app::GameObject*, UnityEngine__GameObject__Find, (app::String* nameFind));
DO_APP_FUNC(0x07BFF870, 0x07C8DFB0, app::Component_1*, UnityEngine_GameObject_GetComponent, (app::GameObject* __this, void* type));
DO_APP_FUNC(0x07BFF7B0, 0x07C8DF00, app::Component_1*, AddComponentInternal, (app::GameObject* __this, app::String* className));
DO_APP_FUNC(0x07BFFDE0, 0x07C8E530, app::Transform*, UnityEngine__Component__get__Transform, (app::GameObject* object));

DO_APP_FUNC(0x07AFDCB0, 0x07B8D1F0, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x07AFDCA0, 0x07B8D1E0, int32_t, UnityEngine_Transform_GetChildCount, (app::Transform* __this));
DO_APP_FUNC(0x07AFF400, 0x07B8D3E0, void, set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07AFDE80, 0x07B8D3F0, void, set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x07AFEFB0, 0x07B8E500, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x07AFDE90, 0x07B8D400, void, set_localScale, (app::Transform* __this, app::Vector3 value));

DO_APP_FUNC(0x07AFA800, 0x07B89DB0, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x07AFA0B0, 0x07B89660, void, Object_1_DestroyImmediate_1, (app::Object_1* obj));

DO_APP_FUNC(0x07AF2B50, 0x07B82150, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));

// UnityEngine
DO_APP_FUNC(0x07BBA680, 0x07C49720, void, RenderSettings_set_fog, (bool value));
DO_APP_FUNC(0x07C01DB0, 0x07C90500, float, Time_get_deltaTime, ());
DO_APP_FUNC(0x07C01F40, 0x07C90690, void*, UnityEngine__set__Timescale, (float time));

DO_APP_FUNC(0x07BDEF60, 0x07C6D7E0, bool*, UnityEngine__Application__get__isFocused, ());
DO_APP_FUNC(0x07BDF5F0, 0x07C6DE70, void*, UnityEngine__Application__set__targetFramerate, (int32_t value));
DO_APP_FUNC(0x07C245D0, 0x07CB2B20, void*, UnityEngine__QualitySettings__set__vSyncCount, (int32_t value));

DO_APP_FUNC(0x07BFD530, 0x07C8BC80, float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));

DO_APP_FUNC(0x07B1A4F0, 0x07BA99D0, bool, Cursor_get_visible, (app::MethodInfo* method));
DO_APP_FUNC(0x07B1A510, 0x07BA99F0, void, Cursor_set_visible, (bool value));
DO_APP_FUNC(0x07B1A500, 0x07BA99E0, void, Cursor_set_lockState, (app::CursorLockMode__Enum value));

DO_APP_FUNC(0x07AFF0B0, 0x07B8E600, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x07AFF480, 0x07B8E9C0, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07AFF180, 0x07B8E6D0, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x07AFF500, 0x07B8EA40, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x07AFF0A0, 0x07B8E5F0, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x07AFF420, 0x07B8E960, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x07AFEAA0, 0x07B8DFF0, void, Transform_Translate, (app::Transform* __this, app::Vector3));

DO_APP_FUNC(0x07A93AF0, 0x07B23800, void, Rigidbody_set_velocity, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x07A93A20, 0x07B23720, void, Rigidbody_set_collisionDetectionMode, (app::Rigidbody* __this, app::CollisionDetectionMode__Enum value));
DO_APP_FUNC(0x07A93A40, 0x07B23740, void, Rigidbody_set_detectCollisions, (app::Rigidbody* __this, bool value));
DO_APP_FUNC(0x07A938E0, 0x07B235E0, app::Vector3, Rigidbody_get_position, (app::Rigidbody* __this));
DO_APP_FUNC(0x07A937C0, 0x07B23500, void, Rigidbody_set_position, (app::Rigidbody* __this, app::Vector3 value));
DO_APP_FUNC(0x07A93800, 0x07B23460, void, Rigidbody_MovePosition, (app::Rigidbody* __this, app::Vector3 value));

DO_APP_FUNC(0x075BD460, 0x07A954B0, void, Action_Invoke, (/*Action*/ void* __this));

// Lua functions
DO_APP_FUNC(0x041A8330, 0x0422AA80, void, MoleMole_LuaShellManager_ReportLuaShellResult, (void* __this, app::String* type, app::String* value));

// Free Camera
DO_APP_FUNC(0x07B39330, 0x07BC81D0, void, Camera_set_fieldOfView, (app::Camera* __this, float value));

// World cheats
DO_APP_FUNC(0x02A3C480, 0x02A8E660, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0x01D243D0, 0x01D56FF0, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));

// Testing.. (401)
//DO_APP_FUNC(0x02D24290, 0x0, bool, Test_inDive, (app::MethodInfo methodInfo));

// Dialog skipping
DO_APP_FUNC(0x02F87B00, 0x02FE38C0, void, MoleMole_TalkDialogContext_OnDialogSelectItem, (app::TalkDialogContext* __this, app::Notify* notify));
DO_APP_FUNC(0x01B1B260, 0x01B48A20, void, MoleMole_InLevelCutScenePageContext_OnFreeClick, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x01B1CC90, 0x01B4A4E0, void, MoleMole_InLevelCutScenePageContext_UpdateView, (app::InLevelCutScenePageContext* __this));
DO_APP_FUNC(0x01B197B0, 0x01B46DF0, void, MoleMole_InLevelCutScenePageContext_ClearView, (app::InLevelCutScenePageContext* __this));

// Skip Cutscene
DO_APP_FUNC(0x04922690, 0x049B1B70, void, CriwareMediaPlayer_Update, (app::CriwareMediaPlayer* __this));
DO_APP_FUNC(0x04922550, 0x049B1A30, void, CriwareMediaPlayer_Skip, (app::CriwareMediaPlayer* __this));

// Chest Indicator
DO_APP_FUNC(0x020D8A30, 0x021165E0, bool, MoleMole_LCIndicatorPlugin_DoCheck, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x020D9DC0, 0x02117970, void, MoleMole_LCIndicatorPlugin_ShowIcon, (app::LCIndicatorPlugin* __this));
DO_APP_FUNC(0x020D8BC0, 0x02116770, void, MoleMole_LCIndicatorPlugin_HideIcon, (app::LCIndicatorPlugin* __this));

// Modify
DO_APP_FUNC(0x033EC7D0, 0x03452BC0, void, MoleMole_HumanoidMoveFSM_LateTick, (app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method));

// Singletons
//idr
//DO_APP_FUNC(0x2191C0, 0x0, void*, Singleton_GetInstance, (app::MethodInfo* method));

// penis id say
//DO_APP_FUNC_METHODINFO(0x09E89398, Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo);

// Protection bypass
DO_APP_FUNC(0x07BDE850, 0x07C6D0D0, app::Byte__Array*, Application_RecordUserData, (int32_t nType, app::MethodInfo* method));

// Skip enhance animation
DO_APP_FUNC(0x027EEB10, 0x0283BF80, void, MoleMole_EquipLevelUpDialogContext_SetupView, (app::MoleMole_EquipLevelUpDialogContext* __this));
DO_APP_FUNC(0x027EDCD0, 0x0283B0F0, void, MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog, (/*MoleMole_EquipLevelUpDialogContext*/ void* __this));
DO_APP_FUNC(0x0412CAA0, 0x041ADB50, void, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, (/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback));
DO_APP_FUNC(0x01D60090, 0x01D93A10, void, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, (/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction));

// Teleport hooks
DO_APP_FUNC(0x02607CF0, 0x02652AF0, void, GameManager_Update, (app::GameManager* __this));

// Open team immediately
DO_APP_FUNC(0x012B43E0, 0x012CC050, bool, MoleMole_InLevelMainPageContext_DoTeamCountDown_c_Iterator0__MoveNext, (app::InLevelMainPageContext_DoTeamCountDown_Iterator* __this));
DO_APP_FUNC(0x02D91F70, 0x02DE99F0, void, MoleMole_InLevelPlayerProfilePageContext_SetupView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));
DO_APP_FUNC(0x02D8E870, 0x02DE60C0, void, MoleMole_InLevelPlayerProfilePageContext_ClearView, (/*MoleMole_InLevelPlayerProfilePageContext*/void* __this));

// Unlimited stamina
DO_APP_FUNC(0x0300BA90, 0x03068F50, void, MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, (app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t HAOCOEMOMBG));
DO_APP_FUNC(0x02746CC0, 0x02792100, void, MoleMole_DataItem_HandleNormalProp, (app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state));
// Wanderer E Stamina
DO_APP_FUNC(0x01C04300, 0x01C34160, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));
