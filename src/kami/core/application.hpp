#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"
#include "swap_chain.hpp"
#include "utils/trait.hpp"
#include "model.hpp"
#include <memory>
#include <vector>
#include <stdexcept>
#include <array>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace kami {
  /**
   * An application tethering all other systems in kami.
  */
  class Application : public NotCopyable {
    public:
      static constexpr int WIDTH = 800;
      static constexpr int HEIGHT = 600;

      Application();
      ~Application();

      void run();
    private:
      void loadModels();
      void createPipelineLayout();
      void createPipeline();
      void createCommandBuffers();
      void freeCommandBuffers();
      void drawFrame();
      void recreateSwapChain();
      void recordCommandBuffer(int imageIndex);

      Window window{WIDTH, HEIGHT, "window name"};
      Device device{window};
      std::unique_ptr<SwapChain> swapChain;//{device, window.getExtent()};
      std::unique_ptr<Pipeline> pipeline;
      VkPipelineLayout pipelineLayout;
      std::vector<VkCommandBuffer> commandBuffers;
      std::unique_ptr<Model> model;
  };
}