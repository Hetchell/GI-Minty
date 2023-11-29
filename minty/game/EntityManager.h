#pragma once

#include <map>
#include <mutex>

#include "Entity.h"
#include "IEntityFilter.h"

namespace cheat::game {
	class EntityManager {
	public:
		static EntityManager& getInstance();

		Entity* entity(app::BaseEntity*);
		Entity* entity(uint32_t runtimeID, bool unsafe = false);

		Entity* avatar();

		std::vector<app::BaseEntity*> rawEntities();
		std::vector<Entity*> entities();
		std::vector<Entity*> entities(const IEntityFilter& filter);
		typedef bool (*Validator)(game::Entity* entity);
		std::vector<Entity*> entities(Validator validator);

		app::CameraEntity* mainCamera();
	private:
		EntityManager();

		std::mutex m_EntityCacheLock;
		std::map<app::BaseEntity*, std::pair<Entity*, uint32_t>> m_EntityCache;

		Entity m_AvatarEntity;

		inline static Entity* s_EmptyEntity = new Entity(nullptr);
	};
}
