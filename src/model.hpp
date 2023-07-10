#pragma once
#include "device.hpp"
#include "not_copyable.hpp"
#include <glm/glm.hpp>

namespace kami {
  class Model : public NotCopyable {
    public:
      Model();
      ~Model();

      void bind(VkCommandBuffer commandBuffer);
      void draw(VkCommandBuffer commandBuffer);

    private:
      Device& device;
      VkBuffer vertexBuffer;
      VkDeviceMemory vertexBufferMemory;
      uint32_t vertexCount;
  };
}