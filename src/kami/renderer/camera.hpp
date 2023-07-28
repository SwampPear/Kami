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
      /**
       * @brief Constructor.
       */
      Camera();

      /**
       * @brief Destructor.
       */
      ~Camera();

      /**
       * @brief Sets the orthographic projection for this Camera and designates
       * this camera as using orthographic projection.
       * @param left the left position of the viewing frustrum
       * @param right the right position of the viewing frustrum
       * @param top the top position of the viewing frustrum
       * @param bottom the bottom position of the viewing frustrum
       * @param near the near position of the viewing frustrum
       * @param far the far position of the viewing frustrum
       */
      void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

      /**
       * @brief Sets the perspective projection for this Camera and designates
       * this camera as using perspective projection.
       * @param fovy the field of view of the viewing frustrum
       * @param aspect the aspect ratio of the viewing frustrum
       * @param near the near position of the viewing frustrum
       * @param far the far position of the viewing frustrum
       */
      void setPerspectiveProjection(float fovy, float aspect, float near, float far);

      /**
       * @brief Sets the direction in which the camera should be looking.
       * @param position position of the camera
       * @param direction direction of the camera
       * @param up up direction of the camera
       */
      void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = {0.0f, -1.0f, 0.0f});

      /**
       * @brief Sets the direction in which the camera should be looking based on
       * a target.
       * @param position position of the camera
       * @param target target camera is directed at
       * @param up up direction of the camera
       */
      void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = {0.0f, -1.0f, 0.0f});

      /**
       * @brief Sets the direction in which the camera should be looking based on
       * a transformation.
       * @param position position of the camera
       * @param rotation rotation of the camera
       */
      void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

      /**
       * @brief Gets the projectionMatrix of this camera.
       */
      const glm::mat4 getProjection() const;

      /**
       * @brief Gets the viewMatrix of this camera.
       */
      const glm::mat4 getView() const;

    private:
      ProjectionType projectionType{ProjectionType::orthographic};
      glm::mat4 projectionMatrix{1.0f};
      glm::mat4 viewMatrix{1.0f};
  };
}