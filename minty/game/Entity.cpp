#include "Entity.h"
#include "EntityManager.h"

namespace cheat::game {
	Entity::Entity(app::BaseEntity* rawEntity) : m_RawEntity(rawEntity), m_HasName(false), m_Name({}) {
	}

	app::BaseEntity* Entity::raw() {
		return m_RawEntity;
	}

	uint32_t Entity::runtimeID() {
		if (m_RawEntity == nullptr)
			return 0;

		return app::MoleMole_BaseEntity_get_runtimeID(m_RawEntity);
	}

	uint32_t Entity::configID() {
		if (m_RawEntity == nullptr)
			return 0;

		return app::MoleMole_BaseEntity_get_configID(m_RawEntity);
	}

	app::EntityType__Enum_1 Entity::type() {
		if (m_RawEntity == nullptr)
			return app::EntityType__Enum_1::None;

		return app::MoleMole_BaseEntity_get_entityType(m_RawEntity);
	}

	app::Vector3 Entity::relativePosition() const {
		if (m_RawEntity == nullptr)
			return {};

		return app::MoleMole_BaseEntity_GetRelativePosition(m_RawEntity);
	}

	bool Entity::isGadget() const {
		if (m_RawEntity == nullptr)
			return false;

		return app::MoleMole_BaseEntity_get_entityType(m_RawEntity) == app::EntityType__Enum_1::Gadget ||
			app::MoleMole_BaseEntity_get_entityType(m_RawEntity) == app::EntityType__Enum_1::Bullet ||
			app::MoleMole_BaseEntity_get_entityType(m_RawEntity) == app::EntityType__Enum_1::Field;
	}

	bool Entity::isAvatar() const {
		if (m_RawEntity == nullptr)
			return false;

		auto avatar = EntityManager::getInstance().avatar();

		if (avatar->raw() == nullptr)
			return false;
		return avatar->raw() == m_RawEntity;
	}

	void Entity::setRelativePosition(const app::Vector3& value) {
		if (m_RawEntity == nullptr)
			return;

		app::MoleMole_BaseEntity_SetRelativePosition(m_RawEntity, value, true);
	}

	bool Entity::isLoaded() const {
		SAFE_BEGIN()
		if (m_RawEntity == nullptr || !app::MoleMole_BaseEntity_IsActive(m_RawEntity))
			return false;

		m_IsLoaded = m_IsLoaded || app::MoleMole_BaseEntity_get_rootGameObject(m_RawEntity);
		SAFE_ERROR()
		return m_IsLoaded;
		SAFE_END()
	}

	app::Animator* Entity::animator() {
		if (!isLoaded())
			return nullptr;

		SAFE_BEGIN();
		return app::MoleMole_BaseEntity_get_animator(m_RawEntity);
		SAFE_ERROR();
		return nullptr;
		SAFE_END();
	}

	app::Rigidbody* Entity::rigidbody() {
		if (!isLoaded())
			return nullptr;

		SAFE_BEGIN();
		return app::MoleMole_BaseEntity_GetRigidbody(m_RawEntity);
		SAFE_ERROR();
		return nullptr;
		SAFE_END();
	}

	app::Vector3 Entity::forward() const {
		if (m_RawEntity == nullptr)
			return {};

		return app::MoleMole_BaseEntity_GetForward(m_RawEntity);
	}

	app::Vector3 Entity::back() const {
		return -forward();
	}

	app::Vector3 Entity::right() const {
		if (m_RawEntity == nullptr)
			return {};

		return app::MoleMole_BaseEntity_GetRight(m_RawEntity);
	}

	app::Vector3 Entity::left() const {
		return -right();
	}

	app::Vector3 Entity::up() const {
		if (m_RawEntity == nullptr)
			return {};

		return app::MoleMole_BaseEntity_GetUp(m_RawEntity);
	}

	app::Vector3 Entity::down() const {
		return -up();
	}
}
