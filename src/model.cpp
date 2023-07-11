#include "model.hpp"

namespace kami{
  Model::Model(Device &device, const std::vector<Vertex> &vertices) : device{device} {
    createVertexBuffers(vertices);
  }

  Model::~Model() {
    vkDestroyBuffer(device.device(), vertexBuffer, nullptr);
    vkFreeMemory(device.device(), vertexBufferMemory, nullptr);
  }
}