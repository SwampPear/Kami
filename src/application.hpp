#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"
#include "swap_chain.hpp"
#include <memory>
#include <vector>
#include <stdexcept>
#include <array>

namespace kami {
  class Application {
    public:
      static constexpr int WIDTH = 800;
      static constexpr int HEIGHT = 600;

      Application();
      ~Application();
      Application(const Application &) = delete;
      Application &operator=(const Application &) = delete;

      void run();
    private:
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
      //Pipeline pipeline{device, "shaders/shader.vert.spv", "shaders/shader.frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
  };
}