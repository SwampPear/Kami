#pragma once

#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"

#include <vulkan/vulkan.h>

#include <memory>
#include <string>
#include <vector>


namespace kami {
  /**
   * @class SwapChain
   * @brief Represents a swap chain for use in integrating the GPU with the
   * rendering system. Not copyable.
   */
  class SwapChain {
    public:
      SwapChain(const SwapChain &) = delete; // prohibit copying
      SwapChain &operator=(const SwapChain &) = delete; // delete copy constructor

      static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
      
    public:
      /**
       * @brief Constructor. Initializes SwapChain object.
       * @param deviceRef reference to the Device class instance
       * @param windowExtent extent of the window surface
       */
      SwapChain(Device &deviceRef, VkExtent2D windowExtent);

      /**
       * @brief Constructor. Initializes SwapChain object with previous SwapChain
       * object for rebuilding this SwapChain.
       * @param deviceRef reference to the Device class instance
       * @param windowExtent extent of the window surface
       * @param previous pointer to previous SwapChain
       */
      SwapChain(Device &deviceRef, VkExtent2D windowExtent, std::shared_ptr<SwapChain> previous);

      /**
       * @brief Destructor. Deallocates all resources properly.
       * @param
       */
      ~SwapChain();

      /**
       * @brief Getter for frame buffer at index.
       * @param index index of frame buffer to return
       * @return frame buffer at index
       */
      VkFramebuffer getFrameBuffer(int index);

      /**
       * @brief Getter for render pass.
       * @return render pass
       */
      VkRenderPass getRenderPass();

      /**
       * @brief Getter for image view at index.
       * @param index index of image view to return.
       * @return image view at index
       */
      VkImageView getImageView(int index);

      /**
       * @brief Returns number of swap chain images.
       * @return number of swap chain images
       */
      size_t imageCount();

      /**
       * @brief Getter for swap chain image format.
       * @return image format
       */
      VkFormat getSwapChainImageFormat();

      /**
       * @brief Getter for swap chain extent.
       * @return swap chain extent
       */
      VkExtent2D getSwapChainExtent();

      /**
       * @brief Getter for swap chain extent width.
       * @return swap chain extent width
       */
      uint32_t width();

      /**
       * @brief Getter for swap chain extent width.
       * @return swap chain extent width
       */
      uint32_t height();

      /**
       * @brief Computes aspect ratio for extent.
       * @return swap chain extent aspect ratio
       */
      float extentAspectRatio();

      /**
       * @brief Returns supported depth format for device.
       * @return supported depth format for device
       */
      VkFormat findDepthFormat();

      /**
       * @brief Retrieves next image to be rendered.
       * @param imageIndex index of current image
       * @return next image
       */
      VkResult acquireNextImage(uint32_t *imageIndex);

      /**
       * @brief Submits command buffers at an index to swap chain.
       * @param buffers command buffers to submit
       * @param imageIndex index to submit buffers at
       * @return result of computation
       */
      VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

      /**
       * @brief Determines if format of next swap chain is identical to previous
       * swap chain.
       * @param swapChain next swap chain
       * @return true if identical, false otherwise
       */
      bool compareSwapFormats(const SwapChain &swapChain) const;

    private:
      VkFormat swapChainImageFormat;
      VkFormat swapChainDepthFormat;
      VkExtent2D swapChainExtent;

      std::vector<VkFramebuffer> swapChainFramebuffers;
      VkRenderPass renderPass;

      std::vector<VkImage> depthImages;
      std::vector<VkDeviceMemory> depthImageMemorys;
      std::vector<VkImageView> depthImageViews;
      std::vector<VkImage> swapChainImages;
      std::vector<VkImageView> swapChainImageViews;

      Device &device;
      VkExtent2D windowExtent;

      VkSwapchainKHR swapChain;
      std::shared_ptr<SwapChain> oldSwapChain;

      std::vector<VkSemaphore> imageAvailableSemaphores;
      std::vector<VkSemaphore> renderFinishedSemaphores;
      std::vector<VkFence> inFlightFences;
      std::vector<VkFence> imagesInFlight;
      size_t currentFrame = 0;

    private:
      /**
       * @brief Initializes swap chain, image views, render pass, depth 
       * resources, frame buffers, and sync objects.
       */
      void init();

      /**
       * @brief Initializes swap chain.
       */
      void createSwapChain();

      /**
       * @brief Initializes image views.
       */
      void createImageViews();

      /**
       * @brief Initializes depth resources.
       */
      void createDepthResources();

      /**
       * @brief Initializes render pass.
       */
      void createRenderPass();

      /**
       * @brief Initializes frame buffers.
       */
      void createFramebuffers();

      /**
       * @brief Initializes sync objects.
       */
      void createSyncObjects();

      /**
       * @brief Chooses swap chain surface format based on device capabilities.
       * @param availableFormats available formats
       * @return supported surface format
       */
      VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

      /**
       * @brief Chooses swap surface present mode based on device capabilities.
       * @param availablePresentModes available present modes
       * @return supported present modes
       */
      VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

      /**
       * @brief Chooses swap surface extent based on device capabilities.
       * @param capabilites capabilities of device
       * @return swap extent
       */
      VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
  };
}