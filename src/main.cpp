#include "exampleApplication/exampleApplication.cpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    ExampleApplication app{};

    try {
        app.run();
    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}