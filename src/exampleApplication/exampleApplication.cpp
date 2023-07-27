#include <kami.hpp>
#include <iostream>


class ExampleApplication : public kami::Application {
  public:
    ExampleApplication() { 
      // setup camera entity
      /*
      kami::Entity cameraEntity = scene.createEntity();

      cameraEntity.addComponent<kami::CameraComponent>();

      auto &camera = scene.getAllEntitiesWith<kami::CameraComponent>().get<kami::CameraComponent>(cameraEntity);

      camera.camera = new kami::Camera();
      camera.camera->setViewTarget(glm::vec3{-1.0f, -2.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 2.5f});

      // setup object entities
      kami::UUID pearID = resourceManager.loadModel("models/pear.obj");
      kami::Entity entity = scene.createEntity();

      entity.addComponent<kami::ColorComponent>();
      entity.addComponent<kami::ModelComponent>();

      auto entitiesView = scene.getAllEntitiesWith<kami::TransformComponent, kami::ModelComponent>();

      auto &transform = entitiesView.get<kami::TransformComponent>(entity);
      transform.translation = {0.0f, 0.0f, 2.5f};
      transform.scale = {0.5f, 0.5f, 0.5f};

      auto &model = entitiesView.get<kami::ModelComponent>(entity);
      model.ID = pearID;
      */
      //cameraController = new kami::CameraController{camera.camera};
    };

    ~ExampleApplication() { };

    kami::Scene scene{};

    //kami::CameraController cameraController;

    virtual void onUpdate(kami::DeltaTime dt) override {
      std::cout << "called from example" << std::endl;
    }
};