#pragma once
#include "device.hpp"

namespace kami {
  class Model {
    public:
      Model();
      ~Model();

    private:
      Device& device;
      VkBuffer vertexBuffer;
      VkDeviceMemory vertexBufferMemory;
      uint32_t vertexCount;
  };
}