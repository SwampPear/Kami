#pragma once

#include "kami/renderer/window.hpp"
#include "kami/core/device.hpp"
#include "kami/renderer/renderer.hpp"
#include "kami/input/input.hpp"
#include "kami/renderer/descriptors.hpp"
#include "kami/resourceManager/resourceManager.hpp"
#include "kami/core/deltaTime.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <stdexcept>
#include <array>
#include <iostream>


namespace kami {
  class Application {
    public:
      Application(const Application &) = delete;
      Application &operator=(const Application &) = delete;

    public:
      static constexpr int WIDTH = 600;
      static constexpr int HEIGHT = 600;

      Application();
      ~Application();

      void run();
      static Application& get() { return *instance; }
      GLFWwindow *getWindow() { return window.getGLFWwindow(); }

      virtual void onUpdate(DeltaTime dt) { std::cout << "called from app" << std::endl;};
      
    private:
      static Application *instance;
      Window window{WIDTH, HEIGHT, "window name"};
      Device device{window};
      ResourceManager resourceManager{device};
      Renderer renderer{window, device, resourceManager};
      std::unique_ptr<DescriptorPool> globalPool{};
  };
}