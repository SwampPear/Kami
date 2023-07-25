#include "kami/input/input.hpp"
#include "kami/core/application.hpp"


namespace kami {
  //auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		//auto state = glfwGetKey(window, static_cast<int32_t>(key));
		//return state == GLFW_PRESS;


  bool Input::isKeyPressed(KeyCode key) { 
    auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getGLFWwindow());
    return glfwGetKey(window, static_cast<int32_t>(key)) == GLFW_PRESS; 
  }

  bool Input::isMouseButtonPressed(MouseCode button) {
    auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getGLFWwindow());
    return glfwGetMouseButton(window, static_cast<int32_t>(button)) == GLFW_PRESS;
  }

  glm::vec2 Input::getMousePosition() {
    auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getGLFWwindow());
    
    double xPos, yPos;

    glfwGetCursorPos(window, &xPos, &yPos);

    return {static_cast<float>(xPos), static_cast<float>(yPos)};
  }

  float Input::getMouseX() { return getMousePosition()[0]; }
  float Input::getMouseY() { return getMousePosition()[1]; }
}