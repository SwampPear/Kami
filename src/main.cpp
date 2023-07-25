#include "exampleApplication/exampleApplication.cpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    ExampleApplication app{};

    try {
        //app.run();
        std::cout << "test" << std::endl;
    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
} //20-7:48