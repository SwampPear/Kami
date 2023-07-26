#include "kami/resourceManager/resourceManager.hpp"


namespace kami {
  ResourceManager::ResourceManager(Device &device) : device{device} { }

  UUID ResourceManager::loadModel(const std::string &fileName) {
    UUID id = UUID();

    modelMap[id] = std::make_shared<Model>(device, fileName);

    //modelMap[id] = new Model(device, fileName);;

    return id;
  }

  void ResourceManager::unloadModel(UUID id) {
    //delete modelMap[id];
    modelMap.erase(id);
  }

  std::shared_ptr<Model> ResourceManager::getModel(UUID id) {
    std::shared_ptr<Model> model = modelMap[id];
    //Model *i = modelMap[id];
    return model;
  }
}