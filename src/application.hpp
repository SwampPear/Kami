#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"
#include "swap_chain.hpp"
#include "util/trait.hpp"
#include "model.hpp"
#include <memory>
#include <vector>
#include <stdexcept>
#include <array>

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

      // will keep these here until I know traits struct work
      //Application(const Application &) = delete;
      //Application &operator=(const Application &) = delete;

      void run();
    private:
      void loadModels();
      void createPipelineLayout();
      void createPipeline();
      void createCommandBuffers();
      void drawFrame();

      Window window{WIDTH, HEIGHT, "window name"};
      Device device{window};
      SwapChain swapChain{device, window.getExtent()};
      std::unique_ptr<Pipeline> pipeline;
      VkPipelineLayout pipelineLayout;
      std::vector<VkCommandBuffer> commandBuffers;
      std::unique_ptr<Model> model;
  };
}