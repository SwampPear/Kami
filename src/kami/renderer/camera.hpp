#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <cassert>
#include <limits>

namespace Kami {
  /**
   * @enum ProjectionType
   * @brief Type of projection the camera is currently using.
   */
  enum class ProjectionType { orthographic, perspective };

  /**
   * @class Camera
   * @brief Represents a camera object that determines rendering of graphics,
   * viewing frustrum, and projection matrices.
   */
  class Camera {
    public:
      Camera() { };
      ~Camera() { };

      void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
      void setPerspectiveProjection(float fovy, float aspect, float near, float far);
      
      void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = {0.0f, -1.0f, 0.0f});
      void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = {0.0f, -1.0f, 0.0f});
      void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

      const glm::mat4 getProjection() const { return projectionMatrix; };
      const glm::mat4 getView() const { return viewMatrix; };

    private:
      ProjectionType projectionType{ProjectionType::orthographic};
      glm::mat4 projectionMatrix{1.0f};
      glm::mat4 viewMatrix{1.0f};
  };
}