#include "kami/Scene/Scene.hpp"
#include "kami/Scene/Entity.hpp"
#include "kami/Scene/Components.hpp"

#include <glm/glm.hpp>


namespace kami {
	Scene::Scene() { }
	Scene::~Scene() { }


	Entity Scene::CreateEntity(const std::string& name) {
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name) {
		Entity entity{registry.create(), this};
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<mTransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		entityMap[uuid] = entity;

		return entity;
	}

	void Scene::DestroyEntity(Entity entity) {
		entityMap.erase(entity.GetUUID());
		registry.destroy(entity);
	}
}