#pragma once

#include "kami/renderer/pipeline.hpp"
#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"
#include "kami/core/game_object.hpp"
#include "kami/renderer/camera.hpp"

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
      RenderSystem(Device &device, VkRenderPass renderPass);
      ~RenderSystem();

      void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects, const Camera &camera);

    private:
      void createPipelineLayout();
      void createPipeline(VkRenderPass renderPass);

      Device &device;
      std::unique_ptr<Pipeline> pipeline;
      VkPipelineLayout pipelineLayout;
  };
}