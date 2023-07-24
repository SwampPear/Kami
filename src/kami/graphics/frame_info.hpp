#pragma once

#include "kami/graphics/camera.hpp"

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