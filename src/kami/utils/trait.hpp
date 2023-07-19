#pragma once


namespace kami {
  /**
   * @struct NoCopy
   * @brief A struct that prevents copying and assignment through copy 
   * constructors and copy assignment operators. Should be inherited from.
   */
  struct NoCopy {
    NoCopy() {};
    NoCopy(const NoCopy &) = delete; // prohibit copying
    NoCopy &operator=(const NoCopy &) = delete; // delete copy constructor
  };

  /**
   * @struct NoMove
   * @brief A struct that prevents moving and assignment through move
   * constructors and move assignment operators. Should be inherited from.
   */
  struct NoMove {
    NoMove() {};
    NoMove(NoMove &&) = delete; // prohibit moving
    NoMove &operator=(NoMove &&) = delete; // delete move operator
  };

  /**
   * @struct DefaultMove
   * @brief A struct that allows moving and assignment through default move
   * constructors and move assignment operators. Should be inherited from.
   */
  struct DefaultMove {
    DefaultMove() {};
    DefaultMove(DefaultMove &&) = default; // default moving
    DefaultMove &operator=(DefaultMove &&) = delete; // default move operator
  };
}