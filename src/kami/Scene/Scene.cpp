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
		entity.addComponent<TransformComponent>();

		entityMap[uuid] = entity;

		return entity;
	}

	void Scene::destroyEntity(Entity entity) {
		entityMap.erase(entity.GetUUID());
		registry.destroy(entity);
	}
	
	Entity Scene::getPrimaryCameraEntity() {
		auto view = registry.view<CameraComponent>();

		for (auto entity : view) {
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.primary)
				return Entity{entity, this};
		}

		return {};
	}

	template<typename... Components>
	auto Scene::getAllEntitiesWith() {
		return registry.view<Components...>();
	}
}