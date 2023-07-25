#pragma once

#include "kami/core/deltaTime.hpp"

#include <chrono>


namespace kami {
	class Timer {
    public:
      Timer() : currentTime(std::chrono::high_resolution_clock::now()) { }

      float deltaTime() {
        Time newTime = std::chrono::high_resolution_clock::now();
        DeltaTime frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        return frameTime;
      }

    private:
      Time currentTime;
	};
}