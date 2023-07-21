#pragma once

#include "kami/renderer/Camera/Camera.hpp"


namespace kami {
  class PerspectiveCamera : public Camera {
    public:
      void setProjection(float fovy, float aspect, float near, float far);
  };
}