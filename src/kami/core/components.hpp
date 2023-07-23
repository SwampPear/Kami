#pragma once

#include "kami/graphics/model.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <memory>


namespace kami {
  struct TransformComponent {
    glm::vec3 translation{};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 rotation{};

    glm::mat4 mat4();
    glm::mat3 normalMatrix();
  };

  struct ColorComponent{
    glm::vec3 color{};
  };

  struct ModelComponent {
    std::shared_ptr<Model> model{};
  };
}