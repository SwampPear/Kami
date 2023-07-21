#include "kami/renderer/render_system.hpp"

#include "glm/gtc/constants.hpp"


namespace kami {
  struct SimplePushConstantData {
    glm::mat4 transform{1.f};
    glm::mat4 normalMatrix{1.f};
  };

  RenderSystem::RenderSystem(Device &device, VkRenderPass renderPass) : device{device} {
    createPipelineLayout();
    createPipeline(renderPass);
  }

  RenderSystem::~RenderSystem() {
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
  }

  void RenderSystem::createPipelineLayout() {
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushConstantData);

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
      throw std::runtime_error("failed to create pipeline layout");
    }
  }

  void RenderSystem::createPipeline(VkRenderPass renderPass) {
    assert(pipelineLayout != nullptr && "cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfig{};
    Pipeline::defaultPipelineConfigInfo(pipelineConfig);
    pipelineConfig.renderPass = renderPass;
    pipelineConfig.pipelineLayout = pipelineLayout;
    pipeline = std::make_unique<Pipeline>(device, "shaders/shader.vert.spv", "shaders/shader.frag.spv", pipelineConfig);
  }

  void RenderSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects, const Camera &camera) {
    pipeline->bind(commandBuffer);

    auto projectionView = camera.getProjection() * camera.getView(); 

    for (auto& gameObject : gameObjects) {
      SimplePushConstantData push{};
      auto modelMatrix = gameObject.transform.mat4();
      push.transform = projectionView * modelMatrix;
      push.normalMatrix = gameObject.transform.normalMatrix();

      vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SimplePushConstantData), &push);
      gameObject.model->bind(commandBuffer);
      gameObject.model->draw(commandBuffer);
    }
  }
}