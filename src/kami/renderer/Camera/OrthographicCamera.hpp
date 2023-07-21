#pragma once

#include "kami/renderer/Camera/Camera.hpp"


namespace kami {
  class OrthographicCamera : public Camera {
    public:
      void setProjection(float left, float right, float top, float bottom, float near, float far);

    private:
      friend class Camera;
  };
}