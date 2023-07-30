#pragma once

#include <vulkan/vulkan.h>

namespace Kami {
  struct FrameInfo {
    int frameIndex;
    float frameTime;
    VkCommandBuffer commandBuffer;
    VkDescriptorSet globalDescriptorSet;
  };
}