#pragma once

#include "kami/core/uuid.hpp"
#include "kami/graphics/model.hpp"

#include <memory>


namespace kami {
  class AssetManager {
    public:
      AssetManager();

      void addModel(std::shared_ptr<Model> model);
    private:
      std::unordered_map<UUID, std::shared_ptr<Model>, HashUUID> modelMap;
  };
}