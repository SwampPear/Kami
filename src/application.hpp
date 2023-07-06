#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"

namespace kami {
  class Application {
    public:
      static constexpr int WIDTH = 800;
      static constexpr int HEIGHT = 600;

      void run();
    private:
      Window window{WIDTH, HEIGHT, "window name"};
      Device device{window};
      Pipeline pipeline{device, "shaders/shader.vert.spv", "shaders/shader.frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
  };
}