#pragma once

#include "kami/utils/trait.hpp"
#include "kami/renderer/model.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <memory>


namespace kami {
  struct TransformComponent {
    glm::vec3 translation{};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 rotation{};

    glm::mat4 mat4() { 
      auto transform = glm::translate(glm::mat4{1.0f}, translation);

      transform = glm::rotate(transform, rotation.y, {0.0f, 1.0f, 0.0f});
      transform = glm::rotate(transform, rotation.x, {1.0f, 0.0f, 0.0f});
      transform = glm::rotate(transform, rotation.z, {0.0f, 0.0f, 1.0f});

      transform = glm::scale(transform, scale);

      return transform;
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
      TransformComponent transform{};

    private:
      GameObject(id_t idObj): id{idObj} {};

      id_t id;
  };
}