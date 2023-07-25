#include "kami/input/input.hpp"
#include "kami/core/application.hpp"


namespace kami {
  bool Input::isKeyPressed(KeyCode key) {
    GLFWwindow* window = Application::get().getWindow();
    return glfwGetKey(window, static_cast<int32_t>(key)) == GLFW_PRESS; 
  }

  bool Input::isMouseButtonPressed(MouseCode button) {
    GLFWwindow* window = Application::get().getWindow();
    return glfwGetMouseButton(window, static_cast<int32_t>(button)) == GLFW_PRESS;
  }

  glm::vec2 Input::getMousePosition() {
    GLFWwindow* window = Application::get().getWindow();

    double xPos, yPos;

    glfwGetCursorPos(window, &xPos, &yPos);

    return { static_cast<float>(xPos), static_cast<float>(yPos) };
  }

  float Input::getMouseX() { return getMousePosition()[0]; }
  float Input::getMouseY() { return getMousePosition()[1]; }
}