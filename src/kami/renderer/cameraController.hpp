#pragma once


#include "kami/renderer/window.hpp"
//#include "kami/renderer/camera.hpp"
#include "kami/scene/scene.hpp"

#include <glm/glm.hpp>


namespace kami {
  class CameraController {
    public:
      CameraController() {};

      void moveInPlaneXZ(float dt, Scene &scene);

      float moveSpeed{3.0f};
      float lookSpeed{1.5f};
  };
}