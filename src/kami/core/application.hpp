#pragma once

#include "kami/renderer/window.hpp"
#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"
#include "kami/core/game_object.hpp"
#include "kami/renderer/renderer.hpp"
#include "kami/input/input.hpp"

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
      static constexpr int WIDTH = 800;
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
      std::vector<GameObject> gameObjects;
  };
}