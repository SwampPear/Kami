#pragma once

#include "kami/core/uuid.hpp"
#include "kami/graphics/camera.hpp"
#include "entt/entt.hpp"

namespace kami {
  class Entity;

	class Scene {
    public:
      Scene();
      ~Scene();

      Entity createEntity();
      Entity createEntityWithUUID(UUID uuid);
      void destroyEntity(Entity entity);

      Entity getPrimaryCameraEntity();

      template<typename... Components>
      auto GetAllEntitiesWith();

    private:
      entt::registry registry;
      std::unordered_map<UUID, entt::entity, HashUUID> entityMap;
      friend class Entity;
  };
}