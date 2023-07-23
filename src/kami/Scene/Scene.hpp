#pragma once

#include "kami/Scene/UUID.hpp"
#include "entt/entt.hpp"

namespace kami {
  class Entity;

	class Scene {
    public:
      Scene();
      ~Scene();

      //static Ref<Scene> Copy(Ref<Scene> other);

      Entity createEntity();
      Entity createEntityWithUUID(UUID uuid);
      void destroyEntity(Entity entity);

      //void OnUpdateRuntime(Timestep ts);
      //void OnUpdateSimulation(Timestep ts, EditorCamera& camera);
      //void OnUpdateEditor(Timestep ts, EditorCamera& camera);
      //void OnViewportResize(uint32_t width, uint32_t height);

      //Entity DuplicateEntity(Entity entity);

      //Entity FindEntityByName(std::string_view name);
      //Entity GetEntityByUUID(UUID uuid);

      //Entity GetPrimaryCameraEntity();


      //void Step(int frames = 1);

      /*
      
      template<typename... Components>
      auto GetAllEntitiesWith()
      {
        return m_Registry.view<Components...>();
      }
      */

    private:
      //template<typename T> void OnComponentAdded(Entity entity, T& component);
      //template<typename T>
		  //void OnComponentAdded(Entity entity, T& component);
      //void RenderScene(EditorCamera& camera);
      //uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

      entt::registry registry;

      std::unordered_map<UUID, entt::entity, HashUUID> entityMap;

      friend class Entity;
  };
}