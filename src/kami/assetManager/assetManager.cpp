#include "kami/assetManager/assetManager.hpp"

#include <iostream>


namespace kami {
  AssetManager::AssetManager(Device &device) : device{device} { }

  UUID AssetManager::addModel(const std::string &fileName) {
    UUID id = UUID();
    Model *m = new Model(device, fileName);

    modelMap[id] = m;

    return id;
  }

  Model* AssetManager::getModel(UUID id) {
    Model *i = modelMap[id]; 
    return i;
  }
}