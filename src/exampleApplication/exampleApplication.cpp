#include <kami.hpp>
#include <iostream>


class ExampleApplication : public kami::Application {
  public:
    ExampleApplication() { };
    ~ExampleApplication() { };

    virtual void onUpdate(kami::DeltaTime dt) override {
      std::cout << "called from example" << std::endl;
    }
};