#include "kami/core/application.hpp"
#include "kami/graphics/render_system.hpp"
#include "kami/graphics/camera/perspectiveCamera.hpp"
#include "kami/graphics/camera/camera.hpp"
#include "kami/graphics/keyboard_movement_controller.hpp"
#include "kami/utils/trait.hpp"
#include "kami/graphics/buffer.hpp"
#include "kami/scene/scene.hpp"
#include "kami/scene/entity.hpp"
#include "kami/core/components.hpp"
#include "kami/scene/components.hpp"

#include "glm/gtc/constants.hpp"

#include <chrono>
#include <iostream>


namespace kami {
  struct GlobalUBO {
    glm::mat4 projectionView{1.0f};
    glm::vec3 lightDirection = glm::normalize(glm::vec3{1.0f, -3.0f, -1.0f});
  };

  Application::Application() {
    globalPool = DescriptorPool::Builder(device)
      .setMaxSets(SwapChain::MAX_FRAMES_IN_FLIGHT)
      .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
      .addPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
      .build();
  }

  Application::~Application() { }

  void Application::run() {
    // ubo buffers
    std::vector<std::unique_ptr<Buffer>> uboBuffers(SwapChain::MAX_FRAMES_IN_FLIGHT);
    for (int i = 0; i < uboBuffers.size(); i++) {
      uboBuffers[i] = std::make_unique<Buffer>(device,
        sizeof(GlobalUBO),
        1,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
      );

      uboBuffers[i]->map();
    }

    // descriptor sets
    auto globalSetLayout = DescriptorSetLayout::Builder(device)
      .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT)
      .build();

    std::vector<VkDescriptorSet> globalDescriptorSets(SwapChain::MAX_FRAMES_IN_FLIGHT);
    for (int i = 0; i < globalDescriptorSets.size(); i++) {
      auto bufferInfo = uboBuffers[i]->descriptorInfo();
      DescriptorWriter(*globalSetLayout, *globalPool)
        .writeBuffer(0, &bufferInfo)
        .build(globalDescriptorSets[i]);
    }

    // rendering
    RenderSystem renderSystem{device, renderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout()};
    PerspectiveCamera camera{};

    camera.setViewTarget(glm::vec3{-1.0f, -2.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 2.5f});

    auto viewObject = GameObject::createGameObject();
    KeyboardMovementController cameraController{};

    // scene
    std::shared_ptr<Model> sphere = Model::createModelFromFile(device, "models/untitled.obj");

    Scene scene{};

    Entity entity = scene.createEntity();
    entity.addComponent<TransformComponent>();
    entity.addComponent<ColorComponent>();

    auto entities = scene.GetAllEntitiesWith<TransformComponent>();

    for (auto e : entities) {
      auto &transform = entities.get<TransformComponent>(e);
      transform.translation = {0.0f, 0.0f, 2.5f};
      transform.scale = {0.5f, 0.5f, 0.5f};
    }

    // main loop
    auto currentTime = std::chrono::high_resolution_clock::now();
    
    while(!window.shouldClose()) {
      glfwPollEvents();

      auto newTime = std::chrono::high_resolution_clock::now();
      float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
      currentTime = newTime;

      cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewObject);
      camera.setViewYXZ(viewObject.transform.translation, viewObject.transform.rotation);

      float aspect = renderer.getAspectRatio();
      camera.setProjection(glm::radians(50.0f), aspect, 0.1f, 10.0f);
      
      if (auto commandBuffer = renderer.beginFrame()) {
        int frameIndex = renderer.getFrameIndex();
        FrameInfo frameInfo{
          frameIndex,
          frameTime,
          commandBuffer,
          camera,
          globalDescriptorSets[frameIndex]
        };

        GlobalUBO ubo{};
        ubo.projectionView = camera.getProjection() * camera.getView();
        uboBuffers[frameIndex]->writeToBuffer(&ubo);
        uboBuffers[frameIndex]->flush();

        renderer.beginSwapChainRenderPass(commandBuffer);
        renderSystem.renderScene(frameInfo, scene, sphere);
        renderer.endSwapChainRenderPass(commandBuffer);
        renderer.endFrame();
      }
    }

    vkDeviceWaitIdle(device.device());
  }
}