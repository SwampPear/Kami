#include "kami/graphics/render_system.hpp"
#include "kami/graphics/camera/camera.hpp"
#include "kami/graphics/model.hpp"
#include "kami/core/components.hpp"
#include "kami/scene/components.hpp"

#include "glm/gtc/constants.hpp"

#include <memory>


namespace kami {
  struct SimplePushConstantData {
    glm::mat4 modelMatrix{1.f};
    glm::mat4 normalMatrix{1.f};
  };

  RenderSystem::RenderSystem(Device &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) : device{device} {
    createPipelineLayout(globalSetLayout);
    createPipeline(renderPass);
  }

  RenderSystem::~RenderSystem() {
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
  }

  void RenderSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushConstantData);
    
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts{globalSetLayout};

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
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

  void RenderSystem::renderScene(FrameInfo &frameInfo, Scene &scene, std::shared_ptr<Model> model) {
    pipeline->bind(frameInfo.commandBuffer);

    vkCmdBindDescriptorSets(
      frameInfo.commandBuffer, 
      VK_PIPELINE_BIND_POINT_GRAPHICS,
      pipelineLayout,
      0,
      1,
      &frameInfo.globalDescriptorSet,
      0,
      nullptr
    );

    //auto projectionView = frameInfo.camera.getProjection() * frameInfo.camera.getView(); 
    auto entities = scene.GetAllEntitiesWith<TransformComponent>();

    for (auto e : entities) {
      auto &transform = entities.get<TransformComponent>(e);

      SimplePushConstantData push{};
      push.modelMatrix = transform.mat4();
      push.normalMatrix = transform.normalMatrix();

      vkCmdPushConstants(frameInfo.commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SimplePushConstantData), &push);
      model->bind(frameInfo.commandBuffer);
      model->draw(frameInfo.commandBuffer);
    }
  }
}