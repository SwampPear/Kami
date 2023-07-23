#include "kami/Scene/Scene.hpp"
#include "kami/Scene/Entity.hpp"
#include "kami/Scene/Components.hpp"

#include <glm/glm.hpp>


namespace kami {
	Scene::Scene() { }
	Scene::~Scene() { }


	Entity Scene::createEntity() {
		return createEntityWithUUID(UUID());
	}

	Entity Scene::createEntityWithUUID(UUID uuid) {
		Entity entity{registry.create(), this};
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<mTransformComponent>();

		entityMap[uuid] = entity;

		return entity;
	}

	void Scene::destroyEntity(Entity entity) {
		entityMap.erase(entity.GetUUID());
		registry.destroy(entity);
	}
}