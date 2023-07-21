#pragma once

#include "kami/input/input.hpp"


namespace kami {
  Input::Input(GLFWwindow *window) {
    window = window;
  }

  Input::~Input() { }

  bool Input::isKeyPressed(KeyCode key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
  }

  bool Input::isMouseButtonPressed(MouseCode button) {
    return glfwMouseButton(window, button) == GLFW_PRESS;
  }

  glm::vec2 Input::getMousePosition() {
    float xPos, yPos;

    glfwGetCursorPos(window, &xPos, &yPos);

    return {xPos, yPos};
  }

  float Input::getMouseX() {
    glm::vec2 mousePos = getMousePosition();
    return mousePos[0];
  }

  float Input::getMouseY() {
    glm::vec2 mousePos = getMousePosition();
    return mousePos[1];
  }
}