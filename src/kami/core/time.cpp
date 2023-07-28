#include "kami/core/time.hpp"


namespace Kami {
  DeltaTime::DeltaTime(float time) : time(time) { }

	DeltaTime::operator float() const { return time; }

	float DeltaTime::seconds() const { return time; }		
  float DeltaTime::milliseconds() const { return time * 1000.0f; }

  Timer::Timer() : currentTime(std::chrono::high_resolution_clock::now()) { }

  void Timer::setCurrentTime() {
    currentTime = std::chrono::high_resolution_clock::now();
  }

  float Timer::deltaTime() {
    Time newTime = std::chrono::high_resolution_clock::now();
    DeltaTime frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
    currentTime = newTime;

    return frameTime;
  }
}