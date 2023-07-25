#include "kami/resourceManager/resourceManager.hpp"


namespace kami {
  ResourceManager::ResourceManager(Device &device) : device{device} { }

  UUID ResourceManager::loadModel(const std::string &fileName) {
    UUID id = UUID();

    modelMap[id] = new Model(device, fileName);;

    return id;
  }

  void ResourceManager::unloadModel(UUID id) {
    delete modelMap[id];
    modelMap.erase(id);
  }

  Model* ResourceManager::getModel(UUID id) {
    Model *i = modelMap[id]; 
    return i;
  }
}