#pragma once

#include "kami/core/uuid.hpp"
#include "entt/entt.hpp"

namespace Kami {
  class Entity;

	class Scene {
    public:
      Scene();
      ~Scene();

      Entity createEntity();
      Entity createEntityWithUUID(UUID uuid);
      void destroyEntity(Entity entity);

      template<typename... Components>
      auto getAllEntitiesWith() {
        return registry.view<Components...>();
      }

    private:
      entt::registry registry;
      std::unordered_map<UUID, entt::entity, HashUUID> entityMap;
      friend class Entity;
  };
}