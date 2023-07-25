#pragma once

#include <glm/glm.hpp>
#include "kami/renderer/window.hpp"
#include "kami/scene/entity.hpp"
#include "kami/renderer/camera.hpp"


namespace kami {
  class CameraController {
    public:
      CameraController(Camera *camera);

      void moveInPlaneXZ(float dt, Scene &scene, Entity entity);

      float moveSpeed{3.0f};
      float lookSpeed{1.5f};
    private:
      Camera *camera;
  };
}