#pragma once

#include "kami/graphics/window.hpp"
#include "kami/core/device.hpp"
#include "kami/graphics/renderer/renderer.hpp"
#include "kami/input/input.hpp"
#include "kami/graphics/descriptors.hpp"
#include "kami/resourceManager/resourceManager.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <stdexcept>
#include <array>


namespace kami {
  class Application {
    public:
      Application(const Application &) = delete;
      Application &operator=(const Application &) = delete;
    public:
      static constexpr int WIDTH = 600;
      static constexpr int HEIGHT = 600;

      Application();
      ~Application();

      void run();
      
    private:
      Window window{WIDTH, HEIGHT, "window name"};
      Device device{window};
      Input input{window};
      ResourceManager resourceManager{device};
      Renderer renderer{window, device, resourceManager};
      std::unique_ptr<DescriptorPool> globalPool{};
  };
}