#pragma once

#include "kami/core/uuid.hpp"
#include "kami/graphics/model.hpp"

#include <memory>


namespace kami {
  class AssetManager {
    public:
      AssetManager();

      UUID addModel(std::shared_ptr<Model> model);
      std::shared_ptr<Model> getModel(UUID id);

    private:
      std::unordered_map<UUID, std::shared_ptr<Model>, HashUUID> modelMap;
  };
}