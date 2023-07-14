#pragma once

#include "utils/trait.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace kami {
  class Window : public NotCopyable {
    public:
      Window(int w, int h, std::string name);
      ~Window();

      bool shouldClose() { return glfwWindowShouldClose(window); };
      VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; };
      bool wasWindowResized() { return framebufferResized; };
      void resetWindowResizedFlag() { framebufferResized = false; };

      void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
    private:
      static void frameBufferResizeCallback(GLFWwindow *window, int width, int height);
      void initWindow();

      int width;
      int height;
      bool framebufferResized = false;

      std::string windowName;

      GLFWwindow *window;
  };
}