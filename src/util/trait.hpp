#pragma once

namespace kami {
  struct NotCopyable {
    NotCopyable() {};
    NotCopyable(const NotCopyable &) = delete;
    NotCopyable &operator=(const NotCopyable &) = delete;
  };

  struct NotMovable {
    NotMovable() {};
    NotMovable(NotMovable &&) = delete;
    NotMovable &operator=(NotMovable &&) = delete;
  };
}