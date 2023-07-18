#include "kami/core/application.hpp"


namespace kami {
  Application::Application() { };
  Application::~Application() { };

  void Application::run() {
    renderer.run();
  }
}