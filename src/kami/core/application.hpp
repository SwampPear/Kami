#pragma once

#include "kami/graphics/window.hpp"
#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"
#include "kami/core/game_object.hpp"
#include "kami/graphics/renderer/renderer.hpp"
#include "kami/input/input.hpp"
#include "kami/graphics/descriptors.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <stdexcept>
#include <array>


namespace kami {
  class Application : public NoCopy {
    public:
      static constexpr int WIDTH = 600;
      static constexpr int HEIGHT = 600;

      Application();
      ~Application();

      void run();
    private:
      void loadGameObjects();

      Window window{WIDTH, HEIGHT, "window name"};
      Device device{window};
      Input input{window};
      Renderer renderer{window, device};
      std::unique_ptr<DescriptorPool> globalPool{};
      std::vector<GameObject> gameObjects;
  };
}