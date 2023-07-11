#pragma once
#include "device.hpp"
#include "not_copyable.hpp"
#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace kami {
  // should use dedicated memory allocator
  class Model : public NotCopyable {
    public:
      struct Vertex {
        glm::vec2 position;

        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
      };

      Model(Device &device, const std::vector<Vertex> &vertices);
      ~Model();

      void bind(VkCommandBuffer commandBuffer);
      void draw(VkCommandBuffer commandBuffer);

    private:
      void createVertexBuffers(const std::vector<Vertex> &vertices);

      Device& device;
      VkBuffer vertexBuffer;
      VkDeviceMemory vertexBufferMemory;
      uint32_t vertexCount;
  };
}