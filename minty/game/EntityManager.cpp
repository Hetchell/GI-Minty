#include "EntityManager.h"

template <typename T>
struct UniList
{
	void* klass;
	void* monitor;
	UniArray<T>* store;
	int32_t size;
	int32_t version;

	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin() { return (*store)[0]; }
	const_iterator begin() const { return (*store)[0]; }
	iterator end() { return (*store)[size]; }
	const_iterator end() const { return (*store)[size]; }

	std::vector<T> vec()
	{
		auto result = std::vector<T>();
		result.reserve(size);
		for (auto i = begin(); i < end(); i++)
			result.push_back(*i);
		return result;
	}
};

#define TO_UNI_COLLECTION(field, collection) reinterpret_cast<collection*>(field)
#define TO_UNI_LIST(field, type) TO_UNI_COLLECTION(field, UniList<type>)

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

	std::vector<app::BaseEntity*> EntityManager::rawEntities()
	{
		auto entityManager = app::MoleMole_InLevelDrumPageContext_get_ENTITY(nullptr);
		if (entityManager == nullptr)
			return {};
		/*LOG_DEBUG("before MoleMole_EntityManager_GetEntities");
		app::MoleMole_EntityManager_GetEntities(entityManager, nullptr);
		LOG_DEBUG("AFTQERELKFJQWEP{JFQWIEI{O MoleMole_EntityManager_GetEntities");*/

		auto entities = TO_UNI_LIST(app::MoleMole_EntityManager_GetEntities(entityManager), app::BaseEntity*);
		if (entities == nullptr)
			return {};

		std::vector<app::BaseEntity*> aliveEntities;
		aliveEntities.reserve(entities->size);

		for (const auto& entity : *entities)
		{
			if (entity != nullptr && app::MoleMole_BaseEntity_IsActive(entity))
				aliveEntities.push_back(entity);
		}
		return aliveEntities;
	}


	std::vector<Entity*> EntityManager::entities()
	{
		std::vector<Entity*> entityVector;
		for (auto& rawEntity : rawEntities())
		{
			auto ent = entity(rawEntity);
			if (ent != s_EmptyEntity)
				entityVector.push_back(ent);
		}
		return entityVector;
	}

	std::vector<Entity*> EntityManager::entities(const IEntityFilter& filter)
	{
		std::vector<Entity*> entityVector;
		for (auto& entity : entities())
		{
			if (filter.IsValid(entity))
				entityVector.push_back(entity);
		}

		return entityVector;
	}

	std::vector<Entity*> EntityManager::entities(Validator validator)
	{
		std::vector<Entity*> entityVector;
		for (auto& entity : entities())
		{
			if (validator(entity))
				entityVector.push_back(entity);
		}

		return entityVector;
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
