#pragma once


#include <entt/entt.hpp>


namespace kami {
  class Scene {
    public:
      Scene() { };
      ~Scene() { };

      void createEntity();
      
    private:
      entt::registry registry;
  };
}