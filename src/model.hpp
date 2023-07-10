#pragma once
#include "device.hpp"

namespace kami {
  class Model {
    public:
      Model();
      ~Model();
      Model(const Model &) = delete;
      Model &operator=(const Model &) = delete;
      
    private:
      Device& device;
      VkBuffer vertexBuffer;
      VkDeviceMemory vertexBufferMemory;
      uint32_t vertexCount;
  };
}