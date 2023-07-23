#pragma once

#include <stdint.h>
#include <cstddef>

namespace kami {
	class UUID {
    public:
      UUID();
      UUID(uint64_t uuid);
      UUID(const UUID&) = default;

      operator uint64_t() const { return m_UUID; }

    private:
      uint64_t m_UUID;
	};

	//template <typename T> struct HashUUID;

	//template<> 
	struct HashUUID {
		size_t operator()(const UUID& uuid) const {
			return static_cast<size_t>((uint64_t)uuid);
		}
	};
}

/*
namespace std {
	template <typename T> struct hash;

	template<> 
	struct hash<kami::UUID> {
		size_t operator()(const kami::UUID& uuid) const {
			return static_cast<size_t>((uint64_t)uuid);
		}
	};
}
*/