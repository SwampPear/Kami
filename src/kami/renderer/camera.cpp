#include "kami/renderer/camera.hpp"

namespace Kami {
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
  void Camera::setOrthographicProjection(float left, float right, float top, float bottom, float near, float far) {
    projectionMatrix = glm::mat4{1.0f};
    projectionMatrix[0][0] = 2.f / (right - left);
    projectionMatrix[1][1] = 2.f / (bottom - top);
    projectionMatrix[2][2] = 1.f / (far - near);
    projectionMatrix[3][0] = -(right + left) / (right - left);
    projectionMatrix[3][1] = -(bottom + top) / (bottom - top);
    projectionMatrix[3][2] = -near / (far - near);

    projectionType = ProjectionType::orthographic;
  }

  /**
   * @brief Sets the perspective projection for this Camera and designates
   * this camera as using perspective projection.
   * @param fovy the field of view of the viewing frustrum
   * @param aspect the aspect ratio of the viewing frustrum
   * @param near the near position of the viewing frustrum
   * @param far the far position of the viewing frustrum
   */
  void Camera::setPerspectiveProjection(float fovy, float aspect, float near, float far) {
    assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
    const float tanHalfFovy = tan(fovy / 2.f);
    projectionMatrix = glm::mat4{0.0f};
    projectionMatrix[0][0] = 1.f / (aspect * tanHalfFovy);
    projectionMatrix[1][1] = 1.f / (tanHalfFovy);
    projectionMatrix[2][2] = far / (far - near);
    projectionMatrix[2][3] = 1.f;
    projectionMatrix[3][2] = -(far * near) / (far - near);

    projectionType = ProjectionType::perspective;
  }

  /**
   * @brief Sets the direction in which the camera should be looking.
   * @param position position of the camera
   * @param direction direction of the camera
   * @param up up direction of the camera
   */
  void Camera::setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up) {
    const glm::vec3 w{glm::normalize(direction)};
    const glm::vec3 u{glm::normalize(glm::cross(w, up))};
    const glm::vec3 v{glm::cross(w, u)};

    viewMatrix = glm::mat4{1.f};
    viewMatrix[0][0] = u.x;
    viewMatrix[1][0] = u.y;
    viewMatrix[2][0] = u.z;
    viewMatrix[0][1] = v.x;
    viewMatrix[1][1] = v.y;
    viewMatrix[2][1] = v.z;
    viewMatrix[0][2] = w.x;
    viewMatrix[1][2] = w.y;
    viewMatrix[2][2] = w.z;
    viewMatrix[3][0] = -glm::dot(u, position);
    viewMatrix[3][1] = -glm::dot(v, position);
    viewMatrix[3][2] = -glm::dot(w, position);
  }

  /**
   * @brief Sets the direction in which the camera should be looking based on
   * a target.
   * @param position position of the camera
   * @param target target camera is directed at
   * @param up up direction of the camera
   */
  void Camera::setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
    setViewDirection(position, target - position, up);
  }

  /**
   * @brief Sets the direction in which the camera should be looking based on
   * a transformation.
   * @param position position of the camera
   * @param rotation rotation of the camera
   */
  void Camera::setViewYXZ(glm::vec3 position, glm::vec3 rotation) {
    const float c3 = glm::cos(rotation.z);
    const float s3 = glm::sin(rotation.z);
    const float c2 = glm::cos(rotation.x);
    const float s2 = glm::sin(rotation.x);
    const float c1 = glm::cos(rotation.y);
    const float s1 = glm::sin(rotation.y);
    const glm::vec3 u{(c1 * c3 + s1 * s2 * s3), (c2 * s3), (c1 * s2 * s3 - c3 * s1)};
    const glm::vec3 v{(c3 * s1 * s2 - c1 * s3), (c2 * c3), (c1 * c3 * s2 + s1 * s3)};
    const glm::vec3 w{(c2 * s1), (-s2), (c1 * c2)};
    viewMatrix = glm::mat4{1.f};
    viewMatrix[0][0] = u.x;
    viewMatrix[1][0] = u.y;
    viewMatrix[2][0] = u.z;
    viewMatrix[0][1] = v.x;
    viewMatrix[1][1] = v.y;
    viewMatrix[2][1] = v.z;
    viewMatrix[0][2] = w.x;
    viewMatrix[1][2] = w.y;
    viewMatrix[2][2] = w.z;
    viewMatrix[3][0] = -glm::dot(u, position);
    viewMatrix[3][1] = -glm::dot(v, position);
    viewMatrix[3][2] = -glm::dot(w, position);
  }
}