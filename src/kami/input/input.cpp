#include "kami/Input/Input.hpp"


namespace kami {
  Input::Input(Window &window) : window{window.getGLFWwindow()} { };
  Input::~Input() { }

  bool Input::isKeyPressed(KeyCode key) { 
    return glfwGetKey(window, key) == GLFW_PRESS; 
  }

  bool Input::isMouseButtonPressed(MouseCode button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
  }

  glm::vec2 Input::getMousePosition() {
    double xPos, yPos;

    glfwGetCursorPos(window, &xPos, &yPos);

    return {static_cast<float>(xPos), static_cast<float>(yPos)};
  }

  float Input::getMouseX() { return getMousePosition()[0]; }
  float Input::getMouseY() { return getMousePosition()[1]; }
}