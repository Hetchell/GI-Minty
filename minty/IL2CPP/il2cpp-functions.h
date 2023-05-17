#include "il2cpp-types.h"
using namespace app;

DO_APP_FUNC(0x00CB8770, void*, MoleMole__ActorUtils__ShowMessage, (void* message));
DO_APP_FUNC(0x00CABB60, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x00CAE150, app::Vector3, MoleMole__ActorUtils__GetAvatarPos, ());
DO_APP_FUNC(0x07B81540, void*, UnityEngine__set__Timescale, (float time));
DO_APP_FUNC(0x07B69AE0, void*, UnityEngine__Application__set__targetFramerate, (int32_t value));
DO_APP_FUNC(0x07BA2190, void*, UnityEngine__QualitySettings__set__vSyncCount, (int32_t value));
DO_APP_FUNC(0x07AB0190, void*, UnityEngine__Transform__set__localScale, (app::Transform* transformComponent, app::Vector3 vectorScale));
DO_APP_FUNC(0x07B7F9C0, app::Transform*, UnityEngine__Component__get__Transform, (app::GameObject* object));
DO_APP_FUNC(0x07B7F430, app::GameObject*, UnityEngine__GameObject__Find, (void* nameFind));
DO_APP_FUNC(0x07B7F7E0, void, UnityEngine__GameObject__SetActive, (app::GameObject* object, bool value));
DO_APP_FUNC(0x00C6D9F0, bool, LCAvatarCombat_IsEnergyMax, (void* __this));
// DO_APP_FUNC(0x00C6E520, bool, LCAvatarCombat_OnSkillStart, (app::LCAvatarCombat* __this, uint32_t skillid, float cdmulti)); -- prolly outdated
DO_APP_FUNC(0x0340D810, float, MoleMole_SafeFloat_get_Value, (SafeFloat safeFloat)); //found with op implicit
DO_APP_FUNC(0x0340D750, SafeFloat, MoleMole_SafeFloat_set_Value, (float safeFloat)); // same
DO_APP_FUNC(0x00C6C700, bool, MoleMole_LCAvatarCombat_IsSkillInCD_1, (LCAvatarCombat* __this, LCAvatarCombat_LCAvatarCombat_SkillInfo* skillInfo));
DO_APP_FUNC(0x07B7F490, app::Component_1*, UnityEngine_GameObject_GetComponent, (app::GameObject* __this, void* type));
DO_APP_FUNC(0x07AB7BC0, void, UnityEngine_Text_setText, (app::Text* __this, void* value));
DO_APP_FUNC(0x013BCAE0, void, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, (MoleMole_VCBaseSetDitherValue* __this, float value));
DO_APP_FUNC(0x036A60B0, void, MoleMole_DataItem_HandleNormalProp, (DataItem* __this, uint32_t type, int64_t value, DataPropOp__Enum state));
DO_APP_FUNC(0x07AAEA10, app::Transform*, UnityEngine_Transform_GetChild, (Transform* __this, int32_t index));
DO_APP_FUNC(0x07AAEA00, int32_t, UnityEngine_Transform_GetChildCount, (Transform* __this));
DO_APP_FUNC(0x01093750, void, VCHumanoidMove_NotifyLandVelocity, (VCHumanoidMove* __this, Vector3 velocity, float reachMaxDownVelocityTime));
DO_APP_FUNC(0x03A0B350, bool, MoleMole_ActorAbilityPlugin_HanlderModifierThinkTimerUp, (ActorAbilityPlugin* __this, float delay, Object* arg));
DO_APP_FUNC(0x07B7F910, bool, UnityEngine_GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x07B7F400, app::GameObject*, UnityEngine_GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
DO_APP_FUNC(0x06F50AC0, app::Vector3, GetRelativePosition, (app::Vector3 __this));
DO_APP_FUNC(0x07AB0170, void, set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07AB0190, void, set_localScale, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07AB0180, void, set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x07B7F390, app::Component_1*, AddComponentInternal, (GameObject* __this, void* className));
DO_APP_FUNC(0x07AAAE80, void, Object_1_DestroyImmediate_1, (app::Object_1* obj)); // -- check another one rva!!!
DO_APP_FUNC(0x07A8EDE0, app::GameObject*, Component_1_get_gameObject, (app::Component_1* __this));
DO_APP_FUNC(0x07AAEA10, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
DO_APP_FUNC(0x07B7F910, bool, GameObject_get_active, (app::GameObject* __this));
DO_APP_FUNC(0x07AAFE10, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x07AAFD20, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x07AAB5C0, app::String*, Object_1_get_name, (app::Object_1* __this));
DO_APP_FUNC(0x07AAFEF0, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x07AAFE20, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x07AB01B0, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));
DO_APP_FUNC(0x07AAEBD0, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x07AAEBC0, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x07B7F8C0, void, GameObject__ctor, (app::GameObject* __this, void* name)); // -- check another 2 rvas!!!
DO_APP_FUNC(0x07ADBBA0, void, Camera_set_fieldOfView, (app::Camera* __this, float value));
DO_APP_FUNC(0x01097C70, void, VCHumanoidMove_Scara, (app::VCHumanoidMove* __this, float value));
DO_APP_FUNC(0x037409D0, void, MoleMole_VCMonsterAIController_TryDoSkill, (void* __this, uint32_t skillID));
DO_APP_FUNC(0x02AE9380, void, MoleMole_LevelSceneElementViewPlugin_Tick, (app::LevelSceneElementViewPlugin* __this, float inDeltaTime));