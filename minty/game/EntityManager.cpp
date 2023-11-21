#include "EntityManager.h"

namespace cheat::game {
	EntityManager::EntityManager() : m_AvatarEntity(nullptr) {
	}

	EntityManager& EntityManager::getInstance() {
		static EntityManager instance;
		return instance;
	}

	Entity* EntityManager::entity(uint32_t runtimeID, bool unsafe) {
		auto entityManager = app::MoleMole_InLevelDrumPageContext_get_ENTITY(nullptr);

		if (entityManager == nullptr)
			return nullptr;

		auto rawEntity = app::MoleMole_EntityManager_GetValidEntity(entityManager, runtimeID);

		if (unsafe)
			return new Entity(rawEntity);
		return entity(rawEntity);
	}

	Entity* EntityManager::avatar() {
		auto entityManager = app::MoleMole_InLevelDrumPageContext_get_ENTITY(nullptr);

		if (entityManager == nullptr)
			return s_EmptyEntity;

		auto avatarRaw = app::MoleMole_EntityManager_GetLocalAvatarEntity(entityManager);

		if (m_AvatarEntity.raw() != avatarRaw)
			m_AvatarEntity = Entity(avatarRaw);
		return &m_AvatarEntity;
	}

	cheat::game::Entity* EntityManager::entity(app::BaseEntity* rawEntity) {
		if (rawEntity == nullptr || !app::MoleMole_BaseEntity_IsActive(rawEntity))
			return s_EmptyEntity;

		std::lock_guard<std::mutex> lock(m_EntityCacheLock);

		if (m_EntityCache.count(rawEntity) > 0) {
			auto& entry = m_EntityCache[rawEntity];

			if (app::MoleMole_BaseEntity_get_runtimeID(rawEntity) == entry.second)
				return entry.first;

			delete m_EntityCache[rawEntity].first;
			m_EntityCache.erase(rawEntity);
			//entityDestroyEvent(entry.first);
		}

		if (app::MoleMole_BaseEntity_get_rootGameObject(rawEntity) == nullptr)
			return s_EmptyEntity;

		Entity* ent = new Entity(rawEntity);
		/*if (ent->isChest()) {
			delete ent;
			ent = new Chest(rawEntity);
		}*/

		m_EntityCache[rawEntity] = { ent, ent->runtimeID() };
		return ent;
	}

	app::CameraEntity* EntityManager::mainCamera() {
		auto entityManager = app::MoleMole_InLevelDrumPageContext_get_ENTITY(nullptr);

		if (entityManager == nullptr)
			return nullptr;

		auto cameraEntity = app::MoleMole_EntityManager_GetMainCameraEntity(entityManager);
		return cameraEntity;
	}
}
