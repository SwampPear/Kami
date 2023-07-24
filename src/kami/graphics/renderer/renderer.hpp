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
  /**
   * @class Renderer
   * @brief Represents a renderer object for rendering graphics and handling all
   * subproccesses.
   */
  class Renderer {
    public:
      Renderer(const Renderer &) = delete; // prohibit copy
      Renderer &operator=(const Renderer &) = delete; // delete copy operator
      
    public:
      /**
       * @brief Constructor. Initializes this Renderer, creates initial swapchain,
       * and creates command buffers.
       */
      Renderer(Window &window, Device &device, ResourceManager &resourceManager);

      /**
       * @brief Destructor. Frees command buffers and destroys pipeline.
       */
      ~Renderer();

      /**
       * @brief Retrieves render pass from swap chain.
       * @return render pass of swap chain
       */
      VkRenderPass getSwapChainRenderPass() const;

      /**
       * @brief Retrieves aspect ratio of the swap chain extent.
       * @return swap chain extent
       */
      float getAspectRatio() const;

      /**
       * @brief Determines if frame is started.
       * @return true if frame is started, false otherwise
       */
      bool isFrameInProgress() const;

      /**
       * @brief Retrieves the current command buffer.
       * @return the command buffer at the current index
       */
      VkCommandBuffer getCurrentCommandBuffer() const;

      /**
       * @brief Retrieves the current frame index.
       * @return the current frame index
       */
      int getFrameIndex() const;

      /**
       * @brief Begins a frame.
       * @return the beginning command buffer
       */
      VkCommandBuffer beginFrame();

      /**
       * @brief Ends a frame.
       */
      void endFrame();

      /**
       * @brief Begins a swapc hain render pass.
       * @param commandBuffer the current command buffer to use
       */
      void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

      /**
       * @brief Ends a swap chain render pass.
       * @param commandBuffer the current command buffer to use
       */
      void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

      /**
       * @brief Renders a scene.
       * @param frameInfo frame info to use for rendering
       * @param scene scene to render
       */
      void renderScene(FrameInfo &frameInfo, Scene &scene);

      /**
       * @brief Creates a pipeline with a descriptor set layout.
       * @param globalSetLayout
       */
      void createPipeline(VkDescriptorSetLayout globalSetLayout);

    private:
      Window &window;
      Device &device;
      std::unique_ptr<SwapChain> swapChain;
      std::vector<VkCommandBuffer> commandBuffers;
      std::unique_ptr<Pipeline> pipeline;
      VkPipelineLayout pipelineLayout;
      ResourceManager &resourceManager;

      uint32_t currentImageIndex;
      int currentFrameIndex{0};
      bool isFrameStarted{false};

    private:
      /**
       * @brief Creates command buffers.
       */
      void createCommandBuffers();

      /**
       * @brief Frees command buffer memory.
       */
      void freeCommandBuffers();

      /**
       * @brief Recreates the swap chain.
       */
      void recreateSwapChain();
  };
}