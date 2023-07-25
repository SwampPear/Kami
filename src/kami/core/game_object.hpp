#pragma once

#include "kami/graphics/model.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <memory>


namespace kami {
  struct TransformComponent1 {
    glm::vec3 translation{};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 rotation{};

    glm::mat4 mat4();
    glm::mat3 normalMatrix();
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
      TransformComponent1 transform{};

    private:
      GameObject(id_t idObj): id{idObj} {};

      id_t id;
  };
}