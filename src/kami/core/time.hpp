#pragma once

#include <chrono>


namespace kami {
  using Time = std::chrono::high_resolution_clock::time_point;

  class DeltaTime {
		public:
			DeltaTime(float time=0.0f);

			operator float() const;

			float seconds() const;
			float milliseconds() const;

		private:
			float time;
	};

	class Timer {
    public:
      Timer();

      float deltaTime();

      void setCurrentTime();

    private:
      Time currentTime;
	};
}