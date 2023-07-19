#pragma once

#include "kami/renderer/window.hpp"
#include "kami/renderer/pipeline.hpp"
#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"
#include "kami/core/game_object.hpp"
#include "kami/renderer/renderer.hpp"

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
      void createPipelineLayout();
      void createPipeline();
      void renderGameObjects(VkCommandBuffer commandBuffer);

      Window window{WIDTH, HEIGHT, "window name"};
      Device device{window};
      Renderer renderer{window, device};
      std::unique_ptr<Pipeline> pipeline;
      VkPipelineLayout pipelineLayout;
      std::vector<GameObject> gameObjects;
  };
}