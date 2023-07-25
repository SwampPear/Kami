#include "kami/renderer/window.hpp"


namespace kami {
  Window::Window(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
    initWindow();
  }

  Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  bool Window::shouldClose() { 
    return glfwWindowShouldClose(window); 
  }

  VkExtent2D Window::getExtent() {
    return {
      static_cast<uint32_t>(width), 
      static_cast<uint32_t>(height)
    };
  }

  bool Window::wasWindowResized() {
    return framebufferResized;
  }

  void Window::resetWindowResizedFlag() {
    framebufferResized = false;
  }

  GLFWwindow* Window::getGLFWwindow() {
    return window;
  }

  void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
      throw std::runtime_error("Failed to create window surface.");
    }
  }

  void Window::frameBufferResizeCallback(GLFWwindow *window, int width, int height) {
    auto p_window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    
    p_window->framebufferResized = true;
    p_window->width = width;
    p_window->height = height;
  }

  void Window::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
  }
}

