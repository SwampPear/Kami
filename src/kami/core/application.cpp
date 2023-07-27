#include "kami/core/application.hpp"
#include "kami/renderer/buffer.hpp"
#include "kami/renderer/camera.hpp"
#include "kami/renderer/cameraController.hpp"
#include "kami/scene/components.hpp"
#include "kami/scene/entity.hpp"
#include "kami/scene/scene.hpp"
#include "kami/resourceManager/resourceManager.hpp"
#include "kami/core/deltaTime.hpp"
#include "kami/core/timer.hpp"

#include <koios/koios.hpp>

#include "glm/gtc/constants.hpp"

#include <iostream>
#include <stdexcept>


namespace kami {
  struct GlobalUBO {
    glm::mat4 projectionView{1.0f};
    glm::vec3 lightDirection = glm::normalize(glm::vec3{1.0f, -3.0f, -1.0f});
  };

  Application* Application::instance = nullptr;

  Application::Application() {
    instance = this;

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

    // create pipeline
    renderer.createPipeline(globalSetLayout->getDescriptorSetLayout());

    // scene - setup entities and scene can be moved to setup method of application
    Scene scene{};

    // camera setup
    Entity cameraEntity = scene.createEntity();
    cameraEntity.addComponent<CameraComponent>();

    auto &camera = scene.getAllEntitiesWith<CameraComponent>().get<CameraComponent>(cameraEntity);

    camera.camera = new Camera();
    camera.camera->setViewTarget(glm::vec3{-1.0f, -2.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 2.5f});

    CameraController cameraController{camera.camera}; // camera controller and camera need to be integrated better

    // entity setup
    UUID pearID = resourceManager.loadModel("models/pear.obj");
    Entity entity = scene.createEntity();

    entity.addComponent<ColorComponent>();
    entity.addComponent<ModelComponent>();

    auto entitiesView = scene.getAllEntitiesWith<TransformComponent, ModelComponent>();

    auto &transform = entitiesView.get<TransformComponent>(entity);
    transform.translation = {0.0f, 0.0f, 2.5f};
    transform.scale = {0.5f, 0.5f, 0.5f};

    auto &model = entitiesView.get<ModelComponent>(entity);
    model.ID = pearID;

    // main loop
    Timer timer{}; // keep timer
    
    while(!window.shouldClose()) {
      glfwPollEvents(); // keep

      DeltaTime dt = timer.deltaTime(); // keep
      onUpdate(dt); // most likely keep, may need to be moved to events system

      // update camera
      cameraController.moveInPlaneXZ(dt, scene, cameraEntity); // can move to onUpdate
      camera.camera->setPerspectiveProjection(glm::radians(50.0f), renderer.getAspectRatio(), 0.1f, 10.0f); // can move to onWindowResize
      
      // update on frame begin
      if (auto commandBuffer = renderer.beginFrame()) {
        // update uniform buffer objects
        int frameIndex = renderer.getFrameIndex();
        FrameInfo frameInfo{
          frameIndex,
          dt,
          commandBuffer,
          globalDescriptorSets[frameIndex]
        };

        GlobalUBO ubo{};
        ubo.projectionView = camera.camera->getProjection() * camera.camera->getView();
        uboBuffers[frameIndex]->writeToBuffer(&ubo);
        uboBuffers[frameIndex]->flush();

        renderer.beginSwapChainRenderPass(commandBuffer);   // step 1
        renderer.renderScene(frameInfo, scene);             // step 2
        renderer.endSwapChainRenderPass(commandBuffer);     // step 3
        renderer.endFrame();                                // step 4
      }
    }

    vkDeviceWaitIdle(device.device());
  }
}