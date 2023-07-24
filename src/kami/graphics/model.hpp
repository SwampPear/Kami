#pragma once

#include "kami/core/device.hpp"
#include "kami/graphics/buffer.hpp"

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

        bool operator==(const Vertex &other) const {
          return position == other.position && color == other.color && normal == other.normal && uv == other.uv;
        }
      };

      void loadModel(const std::string &fileName);

      Model(Device &device, const std::string &fileName);
      ~Model();
      Model(const Model &) = delete; // prohibit copying
      Model &operator=(const Model &) = delete; // delete copy constructor

      static std::unique_ptr<Model> createModelFromFile(Device &device, const std::string &fileName);

      void bind(VkCommandBuffer commandBuffer);
      void draw(VkCommandBuffer commandBuffer);
      bool getd();
      std::vector<Vertex> vertices{};

    private:
      void createVertexBuffers(const std::vector<Vertex> &vertices);
      void createIndexBuffers(const std::vector<uint32_t> &indices);

      Device& device;

      
      std::vector<uint32_t> indices{};
      
      std::unique_ptr<Buffer> vertexBuffer;
      uint32_t vertexCount;

      std::unique_ptr<Buffer> indexBuffer;
      uint32_t indexCount;

      bool hasIndexBuffer{false};
  };
}