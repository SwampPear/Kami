#pragma once

#include "kami/graphics/camera/camera.hpp"


namespace kami {
  class OrthographicCamera : public Camera {
    public:
      void setProjection(float left, float right, float top, float bottom, float near, float far);
  };
}