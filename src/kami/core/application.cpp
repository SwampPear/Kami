#include "kami/core/application.hpp"
#include "kami/utils/trait.hpp"

#include "glm/gtc/constants.hpp"


namespace kami {
  struct SimplePushConstantData {
    glm::mat2 transform{1.f};
    glm::vec2 offset;
    alignas(16) glm::vec3 color;
  };

  Application::Application() {
    loadGameObjects();
    createPipelineLayout();
    createPipeline();
  }

  Application::~Application() {
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
  }

  void Application::run() {
    while(!window.shouldClose()) {
      glfwPollEvents();
      
      if (auto commandBuffer = renderer.beginFrame()) {
        renderer.beginSwapChainRenderPass(commandBuffer);
        renderGameObjects(commandBuffer);
        renderer.endSwapChainRenderPass(commandBuffer);
        renderer.endFrame();
      }
    }

    vkDeviceWaitIdle(device.device());
  }

  void Application::loadGameObjects() {
    std::vector<Model::Vertex> vertices {
      {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, 0.5f}},
      {{-0.5f, 0.5f}}
    };

    auto model = std::make_shared<Model>(device, vertices);

    auto triangle = GameObject::createGameObject();
    triangle.model = model;
    triangle.color = {.1f, .8f, .1f};
    triangle.transform2D.translation.x = .2f;
    triangle.transform2D.scale = {2.0f, 0.5f};
    triangle.transform2D.rotation = 0.25f * glm::two_pi<float>();
    gameObjects.push_back(std::move(triangle));
  }

  void Application::createPipelineLayout() {
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

  void Application::createPipeline() {
    assert(pipelineLayout != nullptr && "cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfig{};
    Pipeline::defaultPipelineConfigInfo(pipelineConfig);
    pipelineConfig.renderPass = renderer.getSwapChainRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    pipeline = std::make_unique<Pipeline>(device, "shaders/shader.vert.spv", "shaders/shader.frag.spv", pipelineConfig);
  }

  void Application::renderGameObjects(VkCommandBuffer commandBuffer) {
    pipeline->bind(commandBuffer);

    for (auto& gameObject : gameObjects) {
      gameObject.transform2D.rotation = glm::mod(gameObject.transform2D.rotation + 0.01f, glm::two_pi<float>());
      SimplePushConstantData push{};
      push.offset = gameObject.transform2D.translation;
      push.color = gameObject.color;
      push.transform = gameObject.transform2D.mat2();

      vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SimplePushConstantData), &push);
      gameObject.model->bind(commandBuffer);
      gameObject.model->draw(commandBuffer);
    }
  }
}