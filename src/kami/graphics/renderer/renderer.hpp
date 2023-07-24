#pragma once

#include "kami/graphics/window.hpp"
#include "kami/core/device.hpp"
#include "kami/graphics/renderer/swapChain.hpp"
#include "kami/graphics/pipeline.hpp"
#include "kami/utils/trait.hpp"
#include "kami/core/game_object.hpp"
#include "kami/graphics/camera.hpp"
#include "kami/graphics/frame_info.hpp"
#include "kami/scene/scene.hpp"
#include "kami/resourceManager/resourceManager.hpp"

#include <memory>
#include <vector>
#include <cassert>


namespace kami {
  class Renderer {
  public:
    Renderer(Window &window, Device &device);
    ~Renderer();

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;

    VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); }
    float getAspectRatio() const { return swapChain->extentAspectRatio(); }
    bool isFrameInProgress() const { return isFrameStarted; }

    VkCommandBuffer getCurrentCommandBuffer() const {
      assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
      return commandBuffers[currentFrameIndex];
    }

    int getFrameIndex() const {
      assert(isFrameStarted && "Cannot get frame index when frame not in progress");
      return currentFrameIndex;
    }

    VkCommandBuffer beginFrame();
    void endFrame();
    void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
    void endSwapChainRenderPass(VkCommandBuffer commandBuffer);
    void renderScene(FrameInfo &frameInfo, Scene &scene, ResourceManager resourceManager);
    void createPipeline(VkDescriptorSetLayout globalSetLayout);

  private:
    void createCommandBuffers();
    void freeCommandBuffers();
    void recreateSwapChain();
    

    Window &window;
    Device &device;
    std::unique_ptr<SwapChain> swapChain;
    std::vector<VkCommandBuffer> commandBuffers;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;

    uint32_t currentImageIndex;
    int currentFrameIndex{0};
    bool isFrameStarted{false};
  };
}