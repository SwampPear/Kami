#pragma once

#include "kami/graphics/pipeline.hpp"
#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"
#include "kami/core/game_object.hpp"
#include "kami/graphics/camera/camera.hpp"
#include "kami/graphics/frame_info.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <stdexcept>
#include <array>


namespace kami {
  class RenderSystem : public NoCopy {
    public:
      RenderSystem(Device &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
      ~RenderSystem();

      void renderGameObjects(FrameInfo &frameInfo, std::vector<GameObject> &gameObjects);

    private:
      void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      void createPipeline(VkRenderPass renderPass);

      Device &device;
      std::unique_ptr<Pipeline> pipeline;
      VkPipelineLayout pipelineLayout;
  };
}