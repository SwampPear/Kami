#include "kami/assetManager/assetManager.hpp"


namespace kami {
  AssetManager::AssetManager() { }

  void AssetManager::addModel(std::shared_ptr<Model> model) {
    modelMap[UUID()] = model;
  }
}