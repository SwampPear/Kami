#pragma once

#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>


namespace kami {
  // should use dedicated memory allocator
  /**
   * A tangible (rendered) object.
  */
  class Model : public NoCopy {
    public:
      struct Vertex {
        glm::vec2 position;
        glm::vec3 color;

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