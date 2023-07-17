#pragma once


namespace kami {
  /**
   * Deletes the copy constructor and copy assignment operator of a parent.
  */
  struct NotCopyable {
    NotCopyable() {};
    NotCopyable(const NotCopyable &) = delete;
    NotCopyable &operator=(const NotCopyable &) = delete;
  };

  /**
   * Deletes the move constructor and move constructor operato of a parent.
  */
  struct NotMovable {
    NotMovable() {};
    NotMovable(NotMovable &&) = delete;
    NotMovable &operator=(NotMovable &&) = delete;
  };
}