#pragma once

#include "kami/core/device.hpp"

#include <string>
#include <vector>


namespace kami {
  /**
   * @struct PipelineConfigInfo
   * @brief Config info for pipeline. 
   */
  struct PipelineConfigInfo {
    PipelineConfigInfo(const PipelineConfigInfo &) = delete;
    PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

    VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    std::vector<VkDynamicState> dynamicStateEnables;
    VkPipelineDynamicStateCreateInfo dynamicStateInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
  };

  /**
   * @class Pipeline
   * @brief Graphics pipeline.
   */
  class Pipeline {
    public:
      Pipeline(const Pipeline &) = delete;
      Pipeline &operator=(const Pipeline &) = delete;

    public:
      /**
       * @brief Constructor.
       * @param device handle to the device to use
       * @param vertFilepath the file name of the vertex shader to use
       * @param fragFilepath the file name of the fragment shader to use
       * @param configInfo config info for creating the pipeline
       */
      Pipeline(
        Device &device, 
        const std::string& vertFilepath, 
        const std::string& fragFilepath, 
        const PipelineConfigInfo& configInfo
      );

      /**
       * @brief Destructor. Destroys shader modules and graphics pipeline.
       */
      ~Pipeline();

      /**
       * @brief Binds a command buffer to the graphics pipeline.
       * @param commandBuffer the command buffer to bind
       */
      void bind(VkCommandBuffer commandBuffer);

      /**
       * @brief Sets a PipelineconfigInfo object to the default pipeline config
       * info.
       * @param configInfo the config info to set
       */
      static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

    private:
      Device& device;
      VkPipeline graphicsPipeline;
      VkShaderModule vertShaderModule;
      VkShaderModule fragShaderModule;
    
    private:
      /**
       * @brief Reads in a file from a file path.
       * @param filepath the path of the file to use
       * @return vector of characters representing the file
       */
      static std::vector<char> readFile(const std::string& filepath);

      /**
       * @brief Creates the graphics pipeline.
       * @param vertFilepath the file path of the vertex shader
       * @param fragFilepath the file path of the fragment shader
       * @param configIngo the config info to use when creating the graphics
       * pipeline
       */
      void createGraphicsPipeline(
        const std::string& vertFilepath, 
        const std::string& fragFilepath, 
        const PipelineConfigInfo& configInfo
      );

      /**
       * @brief Creates a shader module.
       * @param code the contents of the shader file
       * @param shaderModule the shader module to use
       */
      void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
  };
}