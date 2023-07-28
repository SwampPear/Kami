#pragma once

#include <chrono>


namespace Kami {
	/*
	using Time = std::chrono::high_resolution_clock::time_point;

	class DeltaTime {
		public:
			DeltaTime(float time=0.0f, bool clockInit=false) : time(time) { }

			operator float() const { return time; }

			float seconds() const { return time; }
			float milliseconds() const { return time * 1000.0f; }

			
			static float getDeltaTime() {
				Time newTime = std::chrono::high_resolution_clock::now();
				DeltaTime frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
				currentTime = newTime;

				return frameTime;
			}

		private:
			float time;
			//static Time currentTime;
			//static bool clockInit;
		};
		*/
}