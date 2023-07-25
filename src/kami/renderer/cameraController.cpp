#include "kami/renderer/cameraController.hpp"
#include "kami/renderer/camera.hpp"
#include "kami/input/input.hpp"

#include <iostream>


namespace kami {
  CameraController::CameraController(Camera *camera) : camera{camera} { }

  struct KeyMappings {
        int moveLeft = GLFW_KEY_A;
        int moveRight = GLFW_KEY_D;
        int moveForward = GLFW_KEY_W;
        int moveBackward = GLFW_KEY_S;
        int moveUp = GLFW_KEY_E;
        int moveDown = GLFW_KEY_Q;
        int lookLeft = GLFW_KEY_LEFT;
        int lookRight = GLFW_KEY_RIGHT;
        int lookUp = GLFW_KEY_UP;
        int lookDown = GLFW_KEY_DOWN;
      };


  void CameraController::moveInPlaneXZ(GLFWwindow* window, float dt, Scene &scene, Entity entity) {
    auto view = scene.getAllEntitiesWith<TransformComponent, CameraComponent>();

    auto &transform = view.get<TransformComponent>(entity);
    
    glm::vec3 rotate{0.0f};

    if (Input::isKeyPressed(Key::Right)) rotate.y += 1.0f;
    if (Input::isKeyPressed(Key::Left)) rotate.y -= 1.0f;
    if (Input::isKeyPressed(Key::Up)) rotate.x += 1.0f;
    if (Input::isKeyPressed(Key::Down)) rotate.x -= 1.0f;

    if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon()) {
      transform.rotation += lookSpeed * dt * glm::normalize(rotate);
    }

    transform.rotation.x = glm::clamp(transform.rotation.x, -1.5f, 1.5f);
    transform.rotation.y = transform.rotation.y;

    float yaw = transform.rotation.y;
    const glm::vec3 forwardDir{sin(yaw), 0.0f, cos(yaw)};
    const glm::vec3 rightDir{forwardDir.z, 0.0f, -forwardDir.x};
    const glm::vec3 upDir{0.0f, -1.0f, 0.0f};

    glm::vec3 moveDir{0.0f};
    if (Input::isKeyPressed(Key::W)) moveDir += forwardDir;
    if (Input::isKeyPressed(Key::S)) moveDir += -forwardDir;
    if (Input::isKeyPressed(Key::D)) moveDir += rightDir;
    if (Input::isKeyPressed(Key::A)) moveDir += -rightDir;
    if (Input::isKeyPressed(Key::E)) moveDir += upDir;
    if (Input::isKeyPressed(Key::Q)) moveDir += -upDir;

    if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
      transform.translation += moveSpeed * dt * glm::normalize(moveDir);
    }

    camera->setViewYXZ(transform.translation, transform.rotation);

    //camera.camera->setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 10.0f);
  }
}