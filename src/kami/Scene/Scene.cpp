#include "kami/scene/scene.hpp"
#include "kami/scene/entity.hpp"
#include "kami/scene/components.hpp"

#include <glm/glm.hpp>


namespace kami {
	Scene::Scene() { }
	Scene::~Scene() { }


	Entity Scene::createEntity() {
		return createEntityWithUUID(UUID());
	}

	Entity Scene::createEntityWithUUID(UUID uuid) {
		Entity entity{registry.create(), this};
		entity.addComponent<IDComponent>(uuid);
		//entity.addComponent<mTransformComponent>();

		entityMap[uuid] = entity;

		return entity;
	}

	void Scene::destroyEntity(Entity entity) {
		entityMap.erase(entity.GetUUID());
		registry.destroy(entity);
	}
}