#include "il2cpp-types.h"
using namespace app;

DO_APP_FUNC(0x00CB8770, void*, MoleMole__ActorUtils__ShowMessage, (LPVOID message));
DO_APP_FUNC(0x00CABB60, void*, MoleMole__DoSitOnChair, ());
DO_APP_FUNC(0x00CAE150, void*, MoleMole__ActorUtils__GetAvatarPos, ());
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