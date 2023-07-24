#pragma once

#include "kami/core/uuid.hpp"
#include "kami/graphics/model.hpp"
#include "kami/core/device.hpp"

#include <memory>


namespace kami {
  class ResourceManager {
    public:
      ResourceManager(Device &device);

      UUID loadModel(const std::string &fileName);
      void unloadModel(UUID id);
      Model* getModel(UUID id);

    private:
      Device& device;
      std::unordered_map<UUID, Model*, HashUUID> modelMap;
  };
}