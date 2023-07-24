#include "kami/assetManager/assetManager.hpp"


namespace kami {
  AssetManager::AssetManager() { }

  AssetManager::addModel(std::shared_ptr<Model> model) {
    modelMap[UUID()] = model;
  }
}