#pragma once

#include "kami/graphics/camera/camera.hpp"


namespace kami {
  class PerspectiveCamera : public Camera {
    public:
      void setProjection(float fovy, float aspect, float near, float far);
  };
}