#pragma once

#include "kami/renderer/pipeline.hpp"
#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"
#include "kami/core/game_object.hpp"
#include "kami/renderer/Camera/Camera.hpp"
#include "kami/renderer/frame_info.hpp"

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

      void renderGameObjects(FrameInfo &frameInfo, std::vector<GameObject> &gameObjects);

    private:
      void createPipelineLayout();
      void createPipeline(VkRenderPass renderPass);

      Device &device;
      std::unique_ptr<Pipeline> pipeline;
      VkPipelineLayout pipelineLayout;
  };
}