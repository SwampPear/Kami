#include "application.hpp"

namespace kami {
  void Application::run() {
    while(!window.shouldClose()) {
      glfwPollEvents();
    }
  }
}