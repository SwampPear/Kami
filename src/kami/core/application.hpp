#pragma once

#include "kami/renderer/renderer.hpp"
#include "kami/utils/trait.hpp"


namespace kami {
  /**
   * An application tethering all other systems in kami.
  */
  class Application : public NoCopy {
    public:
      Application();
      ~Application();

      void run();
    private:

      Renderer renderer{};
  };
}