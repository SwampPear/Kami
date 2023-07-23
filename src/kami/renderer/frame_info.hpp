#pragma once

#include "kami/renderer/Camera/Camera.hpp"

#include <vulkan/vulkan.h>


namespace kami {
  struct FrameInfo {
    int frameIndex;
    float frameTime;
    VkCommandBuffer commandBuffer;
    Camera &camera;
    VkDescriptorSet globalDescriptorSet;
  };
}