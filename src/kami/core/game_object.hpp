#pragma once

#include "kami/utils/trait.hpp"
#include "kami/renderer/model.hpp"

#include <memory>


namespace kami {
  struct Transform2DComponent {
    glm::vec2 translation{};
    glm::vec2 scale{1.0f, 1.0f};
    float rotation;
    glm::mat2 mat2() { 
      const float s = glm::sin(rotation);
      const float c = glm::cos(rotation);
      glm::mat2 rotMatrix = {{c, s}, {-s, c}};
      glm::mat2 scaleMat{{scale.x, 0.0f}, {0.0f, scale.y}};
      return rotMatrix * scaleMat;
    };
  };

  class GameObject {
    public:
      GameObject(const GameObject &) = delete; // prohibit copying
      GameObject &operator=(const GameObject &) = delete; // delete copy constructor
      GameObject(GameObject &&) = default; // default moving
      GameObject &operator=(GameObject &&) = delete; // default move operator
      using id_t = unsigned int;

      static GameObject createGameObject() {
        static id_t currentId = 0;
        return GameObject{currentId++};
      }

      id_t getId() {
        return id;
      }

      std::shared_ptr<Model> model{};
      glm::vec3 color{};
      Transform2DComponent transform2D{};


    private:
      GameObject(id_t idObj): id{idObj} {};

      id_t id;
  };
}