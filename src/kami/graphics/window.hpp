#pragma once

#include "kami/utils/trait.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>


namespace kami {
  /**
   * @class Window
   * @brief Represents a manipulatable window object on which graphics can be 
   * rendered. Not copyable.
   */
  class Window : public NoCopy {
    public:
      /**
       * @brief Constructor. Initializes the glfw window.
       * @param w initial width of the window
       * @param h initial height of the window
       * @param name name of the window
       */
      Window(int w, int h, std::string name);

      /**
       * @brief Destructor. Destroys the glfw window and terminates glfw.
       */
      ~Window();

      /**
       * @brief Determines if the glfw window should close.
       * @return glfwWindowShouldClose
       */
      bool shouldClose();

      /**
       * @brief Gets the current extent of the window.
       * @return Vulkan extent as {width, height}
       */
      VkExtent2D getExtent();

      /**
       * @brief Determines if the window was resized.
       * @return framebufferResized
       */
      bool wasWindowResized();

      /**
       * @brief Resets the frameBufferResized flag to false;
       */
      void resetWindowResizedFlag();

      /**
       * @brief returns the window member variable
       */
      GLFWwindow* getGLFWwindow();

      /**
       * @brief Creates the surface which graphics are rendered on.
       * @param instance the Vulkan instance
       * @param surface the Vulkan window surface
       */
      void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
      
    private:
      int width;
      int height;

      std::string windowName;

      bool framebufferResized = false;

      GLFWwindow *window;

      /**
       * @brief Callback for resizing window based on GLFWwindow.
       * @param window pointer to GLFWwindow
       * @param width new width of the window
       * @param height new height of the window
       */
      static void frameBufferResizeCallback(GLFWwindow *window, int width, int height);

      /**
       * @brief Initializes GLFW, the GLFWwindow, the GLFWwindow pointer, and the
       * GLFWwindow callback.
       */
      void initWindow();
  };
}