#include "kami/core/application.hpp"
#include "kami/renderer/buffer.hpp"
#include "kami/renderer/camera.hpp"
#include "kami/renderer/cameraController.hpp"
#include "kami/scene/components.hpp"
#include "kami/scene/entity.hpp"
#include "kami/scene/scene.hpp"
#include "kami/resourceManager/resourceManager.hpp"

#include <koios/koios.hpp>

#include "glm/gtc/constants.hpp"

#include <iostream>
#include <stdexcept>


namespace Kami {
  Application* Application::instance = nullptr;

  Application::Application() {
    instance = this;
  }

  Application::~Application() { }

  void Application::run() {
    Timer timer{};
    
    while(!window.shouldClose()) {
      glfwPollEvents();

      DeltaTime dt = timer.deltaTime();
      onUpdate(dt);
    }

    vkDeviceWaitIdle(device.device());
  }
}