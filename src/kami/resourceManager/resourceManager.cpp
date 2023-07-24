#include "kami/resourceManager/resourceManager.hpp"

#include <iostream>


namespace kami {
  ResourceManager::ResourceManager(Device &device) : device{device} { }

  UUID ResourceManager::addModel(const std::string &fileName) {
    UUID id = UUID();

    modelMap[id] = new Model(device, fileName);;

    return id;
  }

  Model* ResourceManager::getModel(UUID id) {
    Model *i = modelMap[id]; 
    return i;
  }
}