#include "MobVacuum.h"

#define UPDATE_DELAY(delay) \
							static ULONGLONG s_LastUpdate = 0;       \
                            ULONGLONG currentTime = GetTickCount64();\
                            if (s_LastUpdate + (delay) > currentTime)  \
                                return;                              \
							s_LastUpdate = currentTime;

namespace cheat
{
	void MobVacuum_GameManager_Update_Hook(app::GameManager* __this, app::MethodInfo* method);
	void MobVacuum_LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq);
	void UpdateFilters();

	MobVacuum::MobVacuum() {
		f_Enabled = config::getValue("functions:MobVacuum", "enabled", false);
		f_Delay = config::getValue("functions:MobVacuum", "delay", 1000);
		f_Distance = config::getValue("functions:MobVacuum", "distance", 1.5f);
		f_Radius = config::getValue("functions:MobVacuum", "radius", 20.f);
		f_Hotkey = Hotkey("functions:MobVacuum");

		HookManager::install(app::MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, MobVacuum_LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook);
		HookManager::install(app::GameManager_Update, MobVacuum_GameManager_Update_Hook);
	}

	MobVacuum& MobVacuum::getInstance()
	{
		static MobVacuum instance;
		return instance;
	}

	void MobVacuum::GUI()
	{
		ConfigCheckbox("Mob Vacuum", f_Enabled, "Enables mob vacuum.\n" \
			"Mobs within the specified radius will move\nto a specified distance in front of the player.");

		if (f_Enabled.getValue()) {
			ImGui::Indent();

			ConfigCheckbox("Monsters", f_IncludeMonsters, "Include monsters in vacuum.");
			if (f_IncludeMonsters.getValue()) {
				ImGui::Indent();

				if (ImGui::BeginCombo("", "Monsters filters")) {
					ConfigCheckbox("Monster common", f_MonsterCommon, "Common enemies.");
					ConfigCheckbox("Monster Elites", f_MonsterElites, "Elite enemies.");
					ConfigCheckbox("MonsterBosses", f_MonsterBosses, "World and Trounce boss enemies.");

					ImGui::EndCombo();
				}
				ImGui::Unindent();

			}
			
			ConfigCheckbox("Animals", f_IncludeAnimals, "Include animals in vacuum.");
			if (f_IncludeAnimals.getValue()) {
				ImGui::Indent();

				if (ImGui::BeginCombo("", "Animals filters")) {
					ConfigCheckbox("Animal drop", f_AnimalDrop, "Animals you need to kill before collecting.");
					ConfigCheckbox("Animal pick up", f_AnimalPickUp, "Animals you can immediately collect.");
					ConfigCheckbox("Animal NPC", f_AnimalNPC, "Animals without mechanics.");

					ImGui::EndCombo();
				}
				ImGui::Unindent();
			}

			UpdateFilters();

			ConfigCheckbox("Instant Vacuum", f_Instantly, "Vacuum entities instantly.");
			ConfigCheckbox("Only Hostile/Aggro", f_OnlyTarget, "If enabled, vacuum will only affect monsters targeting you. Will not affect animals.");
			ConfigCheckbox("Remove Collider", f_SetCollider, "If enabled, monsters won't be able to push you despite the distance or size");
			ConfigSliderFloat("Speed", f_Speed, 0.1f, 15.0f, "If 'Instant Vacuum' is not checked, mob will be vacuumed at the specified speed.");
			ConfigSliderFloat("Radius (m)", f_Radius, 0.1f, 150.0f, "Radius of vacuum.");
			ConfigSliderFloat("Distance (m)", f_Distance, 0.1f, 10.0f, "Distance between the player and the monster.");

			ImGui::Unindent();

		}

	}

	void MobVacuum::Status()
	{
		if (f_Enabled.getValue())
			ImGui::Text("VacuumLoot\n[%dms|%.01fm|%.01fm]",
				f_Delay.getValue(),
				f_Radius.getValue(),
				f_Distance.getValue()
			);
	}

	std::string MobVacuum::getModule() {
		return _("World");
	}

	void MobVacuum::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void UpdateFilters() {
		MobVacuum& mobVacuum = MobVacuum::getInstance();

		mobVacuum.m_Filters.clear();

		if (mobVacuum.f_IncludeMonsters.getValue()) {
			if (mobVacuum.f_MonsterCommon.getValue()) mobVacuum.m_Filters.push_back(&game::filters::combined::MonsterCommon);
			if (mobVacuum.f_MonsterElites.getValue()) mobVacuum.m_Filters.push_back(&game::filters::combined::MonsterElites);
			if (mobVacuum.f_MonsterBosses.getValue()) mobVacuum.m_Filters.push_back(&game::filters::combined::MonsterBosses);
		}

		if (mobVacuum.f_IncludeAnimals.getValue()) {
			if (mobVacuum.f_AnimalDrop.getValue()) mobVacuum.m_Filters.push_back(&game::filters::combined::AnimalDrop);
			if (mobVacuum.f_AnimalPickUp.getValue()) mobVacuum.m_Filters.push_back(&game::filters::combined::AnimalPickUp);
			if (mobVacuum.f_AnimalNPC.getValue()) mobVacuum.m_Filters.push_back(&game::filters::combined::AnimalNPC);
		}
	}

	// Check if entity valid for mob vacuum.
	bool IsEntityForVac(game::Entity* entity)
	{
		MobVacuum& mobVacuum = MobVacuum::getInstance();

		if (mobVacuum.m_Filters.empty())
			return false;

		bool entityValid = std::any_of(mobVacuum.m_Filters.cbegin(), mobVacuum.m_Filters.cend(),
			[entity](const game::IEntityFilter* filter) { return filter->IsValid(entity); });
		if (!entityValid)
			return false;

		auto& manager = game::EntityManager::getInstance();
		if (mobVacuum.f_OnlyTarget.getValue() && game::filters::combined::Monsters.IsValid(entity))
		{
			auto monsterCombat = entity->combat();
			if (monsterCombat == nullptr || monsterCombat->fields._attackTarget.runtimeID != manager.avatar()->runtimeID())
				return false;
		}

		auto distance = manager.avatar()->distance(entity);
		return distance <= mobVacuum.f_Radius.getValue();
	}


	// Calculate mob vacuum target position.
	app::Vector3 CalcMobVacTargetPos()
	{
		auto& manager = game::EntityManager::getInstance();
		MobVacuum& mobVacuum = MobVacuum::getInstance();

		auto avatarEntity = manager.avatar();
		if (avatarEntity == nullptr)
			return {};

		return avatarEntity->relativePosition() + avatarEntity->forward() * mobVacuum.f_Distance.getValue();
	}



	// Set Monster's collider
	// Taiga#5555: There might be an in-game function for this already I'm just not sure which one
	void SetMonsterCollider(bool v)
	{
		UPDATE_DELAY(300);

		auto monsterRoot = app::GameObject_Find(string_to_il2cppi("/EntityRoot/MonsterRoot"));
		if (monsterRoot != nullptr)
		{
			auto transform = app::GameObject_GetComponentByName(monsterRoot, string_to_il2cppi("Transform"));
			auto monsterCount = app::Transform_GetChildCount(reinterpret_cast<app::Transform*>(transform));
			for (int i = 0; i <= monsterCount - 1; i++)
			{
				auto monsters = app::Transform_GetChild(reinterpret_cast<app::Transform*>(transform), i);
				auto monsterGameObject = app::Component_1_get_gameObject(reinterpret_cast<app::Component_1*>(monsters));
				auto monsterTransform = app::GameObject_GetComponentByName(monsterGameObject, string_to_il2cppi("Transform"));
				auto transformChild = app::Transform_GetChild(reinterpret_cast<app::Transform*>(monsterTransform), 1);
				auto colliderGameObject = app::Component_1_get_gameObject(reinterpret_cast<app::Component_1*>(transformChild));
				if (app::GameObject_get_active(colliderGameObject) == v)
					continue;
				app::GameObject_SetActive(colliderGameObject, v);
			}
		}
	}

	inline float GetVectorMagnitude(const app::Vector3& A)
	{
		return sqrtf(A.x * A.x + A.y * A.y + A.z * A.z);
	}

	inline app::Vector3 GetVectorDirection(const app::Vector3& from, const app::Vector3& to)
	{
		auto dirRaw = to - from;
		return dirRaw / GetVectorMagnitude(dirRaw);
	}


	void MobVacuum_GameManager_Update_Hook(app::GameManager* __this, app::MethodInfo* method)
	{
		MobVacuum& mobVacuum = MobVacuum::getInstance();

		static auto positions = new std::map<uint32_t, app::Vector3>();

		if (!(mobVacuum.f_Enabled.getValue()))
			CALL_ORIGIN(MobVacuum_GameManager_Update_Hook, __this, method);


		app::Vector3 targetPos = CalcMobVacTargetPos();

		if (targetPos.x == 0 && targetPos.y == 0 && targetPos.z == 0)
			CALL_ORIGIN(MobVacuum_GameManager_Update_Hook, __this, method);


		UpdateFilters();
		if (!(mobVacuum.f_IncludeMonsters.getValue() && !(mobVacuum.f_IncludeAnimals.getValue())))
			CALL_ORIGIN(MobVacuum_GameManager_Update_Hook, __this, method);

		if (mobVacuum.m_Filters.empty())
			CALL_ORIGIN(MobVacuum_GameManager_Update_Hook, __this, method);

		auto& manager = game::EntityManager::getInstance();
		auto newPositions = new std::map<uint32_t, app::Vector3>();
		for (const auto& entity : manager.entities())
		{
			if (!IsEntityForVac(entity))
				continue;

			SetMonsterCollider(!mobVacuum.f_SetCollider.getValue());

			if (mobVacuum.f_Instantly.getValue())
			{
				entity->setRelativePosition(targetPos);
				continue;
			}

			uint32_t entityId = entity->runtimeID();
			app::Vector3 entityRelPos = positions->count(entityId) ? (*positions)[entityId] : entity->relativePosition();
			app::Vector3 newPosition = {};
			if (app::Vector3_Distance(entityRelPos, targetPos) < 0.1)
			{
				newPosition = targetPos;
			}
			else
			{
				app::Vector3 dir = GetVectorDirection(entityRelPos, targetPos);
				float deltaTime = app::Time_get_deltaTime();
				newPosition = entityRelPos + dir * mobVacuum.f_Speed.getValue() * deltaTime;
			}

			(*newPositions)[entityId] = newPosition;
			entity->setRelativePosition(newPosition);
		}

		delete positions;
		positions = newPositions;


		CALL_ORIGIN(MobVacuum_GameManager_Update_Hook, __this, method);
	}

	void MobVacuum_LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq)	
	{
		MobVacuum& mobVacuum = MobVacuum::getInstance();


		if (!mobVacuum.f_Enabled.getValue() || mobVacuum.f_Instantly.getValue())
			return;

		auto& manager = game::EntityManager::getInstance();
		auto entity = manager.entity(entityId);
		if (!IsEntityForVac(entity))
			return;

		SetMonsterCollider(!mobVacuum.f_SetCollider.getValue());

		app::Vector3 targetPos = CalcMobVacTargetPos();
		app::Vector3 entityPos = entity->relativePosition();
		if (app::Vector3_Distance(targetPos, entityPos) < 0.2)
			return;

		app::Vector3 dir = GetVectorDirection(targetPos, entityPos);
		app::Vector3 scaledDir = dir * mobVacuum.f_Speed.getValue();

		syncInfo->fields.speed_->fields.x = scaledDir.x;
		syncInfo->fields.speed_->fields.y = scaledDir.y;
		syncInfo->fields.speed_->fields.z = scaledDir.z;

		switch (syncInfo->fields.motionState)
		{
		case app::MotionState__Enum::MotionStandby:
		case app::MotionState__Enum::MotionStandbyMove:
		case app::MotionState__Enum::MotionWalk:
		case app::MotionState__Enum::MotionDangerDash:
			syncInfo->fields.motionState = app::MotionState__Enum::MotionRun;
		}
	}

}