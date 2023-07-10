#pragma once

namespace kami {
  class NotMovable {
    public:
      NotMovable() {};
      NotMovable(NotMovable &&) = delete;
      NotMovable &operator=(NotMovable &&) = delete;
  };
}