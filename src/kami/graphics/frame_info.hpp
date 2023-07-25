#pragma once

#include <vulkan/vulkan.h>


namespace kami {
  struct FrameInfo {
    int frameIndex;
    float frameTime;
    VkCommandBuffer commandBuffer;
    VkDescriptorSet globalDescriptorSet;
  };
}