#include "application.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    kami::Application app{};

    try {
        app.run();
    } catch (const std::exception &e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// 6-13:15