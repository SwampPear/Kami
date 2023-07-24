#include "kami/assetManager/assetManager.hpp"


namespace kami {
  AssetManager::AssetManager() { }

  UUID AssetManager::addModel(std::shared_ptr<Model> model) {
    UUID id = UUID();

    modelMap[UUID()] = model;

    return id;
  }

  std::shared_ptr<Model> AssetManager::getModel(UUID id) {
    return modelMap[id];
  }
}