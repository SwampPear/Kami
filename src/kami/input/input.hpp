#pragma once

#include "kami/input/keyCodes.hpp"
#include "kami/input/mouseCodes.hpp"
#include "kami/renderer/window.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>


namespace kami {
  class Input {
    public:
      /**
       * @brief Determines if a certain key is pressed.
       * @param key the key to check
       * @return true if key is pressed, false otherwise
       */
      static bool isKeyPressed(KeyCode key);

      /**
       * @brief Determines if a certain mouse button is pressed.
       * @param button the button to check
       * @return true if button is pressed, false otherwise
       */
		  static bool isMouseButtonPressed(MouseCode button);

      /**
       * @brief Computes the mouse position.
       * @return mouse position as {x, y}
       */
      static glm::vec2 getMousePosition();

      /**
       * @brief Computes the x component of mouse position.
       * @return x component of mouse position
       */
		  static float getMouseX();

      /**
       * @brief Computes the y component of mouse position.
       * @return y component of mouse position
       */
		  static float getMouseY();
  };
}