#pragma once

#include <Arduino.h>
#include "types.h"
namespace utils
	{
	class loop
		{
		public:
			inline loop(time_t target_delay) : target_delay{target_delay} {}

			inline void run() noexcept
				{
				while(running)
					{
					step();

					delta_time = current_time() - time_previous;
					if (delta_time < target_delay) { loop::delay(target_delay - delta_time); }

					time_previous = current_time();
					}
				}

			bool running{true};

			virtual void step() noexcept = 0;

		protected:
			inline time_t get_delta_time() noexcept { return delta_time; }

		private:
			inline time_t current_time() noexcept { return ::micros(); }
			inline void delay(time_t time) noexcept { ::delay(time); }
			time_t target_delay{0};
			time_t delta_time{0};
			time_t time_previous{0};
		};
	}