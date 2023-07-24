#include "kami/core/application.hpp"
#include "kami/graphics/camera.hpp"
#include "kami/graphics/keyboard_movement_controller.hpp"
#include "kami/utils/trait.hpp"
#include "kami/graphics/buffer.hpp"
#include "kami/scene/scene.hpp"
#include "kami/scene/entity.hpp"
#include "kami/scene/components.hpp"
#include "kami/resourceManager/resourceManager.hpp"

#include "glm/gtc/constants.hpp"

#include <chrono>
#include <iostream>


namespace kami {
  struct GlobalUBO {
    glm::mat4 projectionView{1.0f};
    glm::vec3 lightDirection = glm::normalize(glm::vec3{1.0f, -3.0f, -1.0f});
  };

  Application::Application() {
    // create descriptor pool
    globalPool = DescriptorPool::Builder(device)
      .setMaxSets(SwapChain::MAX_FRAMES_IN_FLIGHT)
      .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
      .addPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
      .build();
  }

  Application::~Application() { }

  void Application::run() {
    // create uniform buffer objects
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

    // create decsriptor set layouts
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

    // resource management
    UUID sphereID = resourceManager.loadModel("models/untitled.obj");
    UUID crystalID = resourceManager.loadModel("models/pear.obj");

    // scene setup
    Scene scene{};

    Entity entity = scene.createEntity();
    Entity entity2 = scene.createEntity();
    
    entity.addComponent<ColorComponent>();
    entity.addComponent<ModelComponent>();
    entity2.addComponent<ColorComponent>();
    entity2.addComponent<ModelComponent>();

    auto entities = scene.getAllEntitiesWith<TransformComponent, ModelComponent>();

    auto &transform = entities.get<TransformComponent>(entity);
    transform.translation = {0.0f, 0.0f, 2.5f};
    transform.scale = {0.5f, 0.5f, 0.5f};

    auto &transform2 = entities.get<TransformComponent>(entity2);
    transform2.translation = {0.0f, -1.5f, 2.5f};
    transform2.scale = {0.5f, 0.5f, 0.5f};

    auto &model = entities.get<ModelComponent>(entity);
    model.ID = sphereID;

    auto &model2 = entities.get<ModelComponent>(entity2);
    model2.ID = crystalID;

    // rendering
    renderer.createPipeline(globalSetLayout->getDescriptorSetLayout());
    Camera camera{};

    camera.setViewTarget(glm::vec3{-1.0f, -2.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 2.5f});

    auto viewObject = GameObject::createGameObject(); // game objects should be removed entirely in favor of using ECS
    KeyboardMovementController cameraController{};

    // main loop
    auto currentTime = std::chrono::high_resolution_clock::now();
    
    while(!window.shouldClose()) {
      glfwPollEvents(); // checks for GLFW events

      // update time
      auto newTime = std::chrono::high_resolution_clock::now();
      float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
      currentTime = newTime;

      // update camera
      cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewObject);
      camera.setViewYXZ(viewObject.transform.translation, viewObject.transform.rotation);
      float aspect = renderer.getAspectRatio();
      camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 10.0f);
      
      // update on frame begin
      if (auto commandBuffer = renderer.beginFrame()) {
        // update uniform buffer objects
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

        renderer.beginSwapChainRenderPass(commandBuffer);   // step 1
        renderer.renderScene(frameInfo, scene);             // step 2
        renderer.endSwapChainRenderPass(commandBuffer);     // step 3
        renderer.endFrame();                                // step 4
      }
    }

    // wait if device commands it
    vkDeviceWaitIdle(device.device());

    // deallocate resource memory, possibly a better solution for this
    resourceManager.unloadModel(sphereID);
    resourceManager.unloadModel(crystalID);
  }
}