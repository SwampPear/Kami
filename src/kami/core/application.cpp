#include "kami/core/application.hpp"
#include "kami/renderer/render_system.hpp"
#include "kami/renderer/Camera/PerspectiveCamera.hpp"
#include "kami/renderer/Camera/Camera.hpp"
#include "kami/renderer/keyboard_movement_controller.hpp"
#include "kami/utils/trait.hpp"
#include "kami/renderer/buffer.hpp"

#include "glm/gtc/constants.hpp"

#include <chrono>


namespace kami {
  struct GlobalUBO {
    glm::mat4 projectionView{1.0f};
    glm::vec3 lightDirection = glm::normalize(glm::vec3{1.0f, -3.0f, -1.0f});
  };

  Application::Application() {
    loadGameObjects();
  }

  Application::~Application() { }

  void Application::run() {
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

    RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
    PerspectiveCamera camera{};
    //camera.setViewDirection(glm::vec3{0.0f}, glm::vec3{0.5f, 0.0f, 1.0f});
    camera.setViewTarget(glm::vec3{-1.0f, -2.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 2.5f});

    auto viewObject = GameObject::createGameObject();
    KeyboardMovementController cameraController{};

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
          camera
        };

        GlobalUBO ubo{};
        ubo.projectionView = camera.getProjection() * camera.getView();
        uboBuffers[frameIndex]->writeToBuffer(&ubo);
        uboBuffers[frameIndex]->flush();

        renderer.beginSwapChainRenderPass(commandBuffer);
        renderSystem.renderGameObjects(frameInfo, gameObjects);
        renderer.endSwapChainRenderPass(commandBuffer);
        renderer.endFrame();
      }
    }

    vkDeviceWaitIdle(device.device());
  }



  void Application::loadGameObjects() {
    std::shared_ptr<Model> model = Model::createModelFromFile(device, "models/pear.obj");

    auto cube = GameObject::createGameObject();
    cube.model = model;
    cube.transform.translation = {0.0f, 0.0f, 2.5f};
    cube.transform.scale = {0.5f, 0.5f, 0.5f};
    gameObjects.push_back(std::move(cube));
  }
}