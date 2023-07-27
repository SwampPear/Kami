#include "exampleApplication/exampleApplication.cpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << "a" << std::endl;
    ExampleApplication app{};
    std::cout << "a" << std::endl;

    try {
        std::cout << "a" << std::endl;
        app.run();
        std::cout << "a" << std::endl;
    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}