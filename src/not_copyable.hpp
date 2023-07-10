#pragma once

namespace kami {
  class NotCopyable {
    public:
      NotCopyable() {};
      NotCopyable(const NotCopyable &) = delete;
      NotCopyable &operator=(const NotCopyable &) = delete;
  };
}