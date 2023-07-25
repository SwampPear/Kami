#pragma once

namespace kami {
	class DeltaTime {
	public:
		DeltaTime(float time = 0.0f) : time(time) { }

		operator float() const { return time; }

		float seconds() const { return time; }
		float milliseconds() const { return time * 1000.0f; }
	private:
		float time;
	};
}