#include <kami.hpp>
#include <iostream>


class ExampleApplication : public Kami::Application {
  struct GlobalUBO {
    glm::mat4 projectionView{1.0f};
    glm::vec3 lightDirection = glm::normalize(glm::vec3{1.0f, -3.0f, -1.0f});
  };

  public:
    ExampleApplication() {
      // create descriptor pool
      globalPool = Kami::DescriptorPool::Builder(getDevice())
      .setMaxSets(Kami::SwapChain::MAX_FRAMES_IN_FLIGHT)
      .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Kami::SwapChain::MAX_FRAMES_IN_FLIGHT)
      .addPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, Kami::SwapChain::MAX_FRAMES_IN_FLIGHT)
      .build();

      // create uniform buffer objects
      uboBuffers = std::vector<std::unique_ptr<Kami::Buffer>>(Kami::SwapChain::MAX_FRAMES_IN_FLIGHT);
      for (int i = 0; i < uboBuffers.size(); i++) {
        uboBuffers[i] = std::make_unique<Kami::Buffer>(getDevice(),
          sizeof(GlobalUBO),
          1,
          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        );

        uboBuffers[i]->map();
      }

      // create decsriptor set layouts
      auto globalSetLayout = Kami::DescriptorSetLayout::Builder(getDevice())
        .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT)
        .build();

      globalDescriptorSets = std::vector<VkDescriptorSet>(Kami::SwapChain::MAX_FRAMES_IN_FLIGHT);
      for (int i = 0; i < globalDescriptorSets.size(); i++) {
        auto bufferInfo = uboBuffers[i]->descriptorInfo();
        Kami::DescriptorWriter(*globalSetLayout, *globalPool)
          .writeBuffer(0, &bufferInfo)
          .build(globalDescriptorSets[i]);
      }

      // create pipeline
      getRenderer().createPipeline(globalSetLayout->getDescriptorSetLayout());
        
      // setup camera entity
      Kami::Entity cameraEntity = scene.createEntity();

      cameraEntity.addComponent<Kami::CameraComponent>();

      auto &camera = scene.getAllEntitiesWith<Kami::CameraComponent>().get<Kami::CameraComponent>(cameraEntity);

      camera.camera = new Kami::Camera();
      camera.camera->setViewTarget(glm::vec3{-1.0f, -2.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 2.5f});

      camera.cameraController = new Kami::CameraController();

      // setup object entities
      Kami::UUID pearID = getResourceManager().loadModel("models/pear.obj");
      Kami::Entity entity = scene.createEntity();

      entity.addComponent<Kami::ColorComponent>();
      entity.addComponent<Kami::ModelComponent>();

      auto entitiesView = scene.getAllEntitiesWith<Kami::TransformComponent, Kami::ModelComponent>();

      auto &transform = entitiesView.get<Kami::TransformComponent>(entity);
      transform.translation = {0.0f, 0.0f, 2.5f};
      transform.scale = {0.5f, 0.5f, 0.5f};

      auto &model = entitiesView.get<Kami::ModelComponent>(entity);
      model.ID = pearID;
    };

    ~ExampleApplication() { };

    Kami::Scene scene{};
    std::unique_ptr<Kami::DescriptorPool> globalPool{};

    std::vector<VkDescriptorSet> globalDescriptorSets;
    std::vector<std::unique_ptr<Kami::Buffer>> uboBuffers;

    virtual void onUpdate(Kami::DeltaTime dt) override {
      // update camera
      auto view = scene.getAllEntitiesWith<Kami::CameraComponent>();

      for (auto entity : view) {
        auto &camera = view.get<Kami::CameraComponent>(entity);

        camera.cameraController->moveInPlaneXZ(dt, scene); // can move to onUpdate
        camera.camera->setPerspectiveProjection(glm::radians(50.0f), getRenderer().getAspectRatio(), 0.1f, 10.0f); // can move to onWindowResize

        // update on frame begin
        if (auto commandBuffer = getRenderer().beginFrame()) {
          // update uniform buffer objects
          int frameIndex = getRenderer().getFrameIndex();
          Kami::FrameInfo frameInfo{
            frameIndex,
            dt,
            commandBuffer,
            globalDescriptorSets[frameIndex]
          };

          GlobalUBO ubo{};
          ubo.projectionView = camera.camera->getProjection() * camera.camera->getView();
          uboBuffers[frameIndex]->writeToBuffer(&ubo);
          uboBuffers[frameIndex]->flush();

          getRenderer().beginSwapChainRenderPass(commandBuffer);   // step 1
          getRenderer().renderScene(frameInfo, scene);             // step 2
          getRenderer().endSwapChainRenderPass(commandBuffer);     // step 3
          getRenderer().endFrame();      
        }                          // step 4
      }
    }
};