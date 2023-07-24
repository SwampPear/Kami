#pragma once

#include "kami/core/uuid.hpp"
#include "kami/graphics/model.hpp"
#include "kami/core/device.hpp"

#include <memory>


namespace kami {
  class AssetManager {
    public:
      AssetManager(Device &device);

      UUID addModel(const std::string &fileName);
      Model* getModel(UUID id);

    private:
      Device& device;
      std::unordered_map<UUID, Model*, HashUUID> modelMap;
  };
}