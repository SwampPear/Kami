#pragma once

#include "kami/core/uuid.hpp"
#include "kami/graphics/model.hpp"
#include "kami/core/device.hpp"

#include <memory>


namespace kami {
  /**
   * @class ResourceManager
   * @brief Handles resource management and retrieval.
   */
  class ResourceManager {
    public:
      /**
       * @brief Constructor.
       * @param device the reference to the device to use in loading models
       */
      ResourceManager(Device &device);

      /**
       * @brief Loads a model from a filename.
       * @param filename the name of the file to load
       * @return the id of the loaded model
       */
      UUID loadModel(const std::string &fileName);

      /**
       * @brief Frees the model from memory and resets the mapping.
       * @param id the id of the model to clear
       */
      void unloadModel(UUID id);

      /**
       * @brief Returns a pointer to a model object at id.
       * @param id the id of the model pointer to retrieve
       * @return pointer to the model object at id
       */
      Model* getModel(UUID id);

    private:
      Device& device;
      std::unordered_map<UUID, Model*, HashUUID> modelMap;
  };
}