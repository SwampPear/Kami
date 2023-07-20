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
        glm::vec3 position;
        glm::vec3 color;

        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
      };

      struct Builder {
        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};
      };

      Model(Device &device, const Model::Builder &builder);
      ~Model();

      void bind(VkCommandBuffer commandBuffer);
      void draw(VkCommandBuffer commandBuffer);

    private:
      void createVertexBuffers(const std::vector<Vertex> &vertices);
      void createIndexBuffers(const std::vector<uint32_t> &indices);

      Device& device;
      VkBuffer vertexBuffer;
      VkDeviceMemory vertexBufferMemory;
      uint32_t vertexCount;

      VkBuffer indexBuffer;
      VkDeviceMemory indexBufferMemory;
      uint32_t indexCount;

      bool hasIndexBuffer{false};
  };
}