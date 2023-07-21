#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <cassert>
#include <limits>


namespace kami {
  class Camera {
    public:
      void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = {0.0f, -1.0f, 0.0f});
      void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = {0.0f, -1.0f, 0.0f});
      void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

      const glm::mat4 getProjection() const { return projectionMatrix; };
      const glm::mat4 getView() const { return viewMatrix; };

    protected:
      glm::mat4 projectionMatrix{1.0f};
      glm::mat4 viewMatrix{1.0f};
  };
}