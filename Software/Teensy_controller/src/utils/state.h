#pragma once

#include <Arduino.h>
#include "types.h"
namespace utils
	{
	struct state
		{
		virtual void   enter() noexcept {};
		virtual void   leave() noexcept {};
		virtual size_t step (utils::time_t delta_time) noexcept {};
		};
	}