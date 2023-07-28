#pragma once

#include <stdint.h>
#include <cstddef>

namespace Kami {
	/**
   * @class UUID
   * @brief Represents a universally unique id used to provide a uniform id for 
	 * any object or component across the engine.
   */
	class UUID {
		public:
			UUID(const UUID &) = default; // default copy
			operator uint64_t() const { return uuid; } // uint64_t casting
			
    public:
			/**
			 * @brief Constructor. Randomly generates a unique id.
			 */
      UUID();

			/**
			 * @brief Constructor. Randomly generates a unique id from a seed id.
			 */
      UUID(uint64_t uuid);

    private:
      uint64_t uuid;
	};

	/**
	 * @struct HashUUID
   * @brief Hashing operator for usage in unordered map.
   */
	struct HashUUID {
		size_t operator()(const UUID& uuid) const {
			return static_cast<size_t>((uint64_t)uuid);
		}
	};
}