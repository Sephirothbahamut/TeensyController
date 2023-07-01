#pragma once

#include <Arduino.h>

namespace utils
	{
	using time_t = decltype(::millis());

	template <typename T>
	struct vec2 { T x, y; };

	using vec2f = vec2<float>;
	}