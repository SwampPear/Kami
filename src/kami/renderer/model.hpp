#pragma once

#include "kami/core/device.hpp"
#include "kami/utils/trait.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>
#include <vector>


namespace kami {
  // should use dedicated memory allocator
  /**
   * A tangible (rendered) object.
  */
  class Model {
    public:
      struct Vertex {
        glm::vec3 position{};
        glm::vec3 color{};
        glm::vec3 normal{};
        glm::vec2 uv{};

        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
      };

      struct Builder {
        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};

        void loadModel(const std::string &fileName);
      };

      Model(Device &device, const Model::Builder &builder);
      ~Model();
      Model(const Model &) = delete; // prohibit copying
      Model &operator=(const Model &) = delete; // delete copy constructor

      static std::unique_ptr<Model> createModelFromFile(Device &device, const std::string &fileName);

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