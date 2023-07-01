#pragma once
#include "../pin.h"
#include <optional>
#include "../../types.h"

namespace utils::hardware::digital
	{
	class button
		{
		public:
			inline constexpr static time_t debounce_delay{50};
			inline button(uint8_t index) : pin{index} {}
			
			inline std::optional<bool> read() noexcept { return update() ? std::optional<bool>{value()} : std::optional<bool>{std::nullopt}; }

			inline bool update()
				{
				time_t now{millis()};
				if(now < reject_until) { return false; }

				bool new_state{pin.read() == LOW};
				if (_state == new_state) { return false; }

				_state = new_state;
				reject_until = now + debounce_delay;
				return true;
				}

			inline bool value() const noexcept { return _state; }

			//updating alternative to read, returns true only if it's released after having been pressed
			inline bool pressed()
				{
				if(update()) { return !value(); }
				return false;
				}

		private:
			pin::digital::input_pullup pin;
			time_t reject_until{0};
			bool _state{false};
			bool was_pressed{false};
		};
	}