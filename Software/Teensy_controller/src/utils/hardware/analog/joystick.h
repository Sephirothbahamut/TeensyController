#pragma once
#include "../pin.h"
#include "../digital/button.h"
#include <optional>

namespace utils::hardware::analog
	{
	namespace details
		{
		float percent(uint16_t value, uint16_t min, uint16_t max)
			{
			uint16_t range{max - min};
			uint16_t minless_value{value - min};
			return static_cast<float>(minless_value) / static_cast<float>(range);
			}
		float range(uint16_t value, uint16_t min, uint16_t zero, uint16_t max)
			{
			return value < zero ? 1 - percent(value, min, zero) : percent(value, zero, max);
			}
		}
	class axis
		{
		public:
			inline axis(uint8_t index) : pin{index} {}

			class calibrator_bounds;
			friend class calibrator_bounds;
			class calibrator_zero;
			friend class calibrator_zero;

			inline std::optional<float> read() noexcept { return update() ? std::optional<float>{value()} : std::optional<float>{std::nullopt}; }

			inline bool update() 
				{
				uint16_t value{pin.read()};
				if(value <= last_value + ignore_delta && value >= last_value - ignore_delta) { return false; }
				
				last_value = value;
				return true;
				}

			inline float value() const noexcept { return details::range(last_value, min, zero, max); }
			inline uint16_t raw_value() const noexcept { return pin.read(); }

		private:
			pin::analog::input pin;

			uint16_t min{0};
			uint16_t max{pin::analog::max};
			uint16_t ignore_delta{10};
			uint16_t zero{(pin::analog::max / 2)};

			uint16_t last_value{zero};
		};
	
	class axis::calibrator_bounds
		{
		public:
			calibrator_bounds(axis& axis) : axis_ptr{&axis} 
				{
				axis_ptr->min = pin::analog::max;
				axis_ptr->max = 0;
				}
			inline void calibrate() 
				{
				uint16_t value{axis_ptr->pin.read()};

				axis_ptr->min = std::min(value, axis_ptr->min);
				axis_ptr->max = std::max(value, axis_ptr->max);
				}

		private:
			axis* axis_ptr;
		};
	class axis::calibrator_zero
		{
		public:
			calibrator_zero(axis& axis) : axis_ptr{&axis} {}
			inline void calibrate()
				{
				uint16_t value{axis_ptr->pin.read()};

				min_zero = std::min(value, min_zero);
				max_zero = std::max(value, max_zero);

				axis_ptr->ignore_delta = ((max_zero - min_zero) / 2) + 1;
				axis_ptr->zero = min_zero + axis_ptr->ignore_delta;
				}

		private:
			axis* axis_ptr;

			uint16_t min_zero{(pin::analog::max / 2)};
			uint16_t max_zero{(pin::analog::max / 2)};
		};

	class joystick
		{
		public:
			inline joystick(axis x, axis y, digital::button button) : x{x}, y{y}, button{button} {}

			axis x;
			axis y;
			digital::button button;

			inline void update()
				{
				axes_update();
				button.update();
				}

			inline std::optional<vec2f> axes_read() noexcept { return axes_update() ? std::optional<vec2f>{axes_value()} : std::optional<vec2f>{std::nullopt}; }
			inline bool axes_update() noexcept { return x.update() + y.update(); }
			inline vec2f axes_value() const noexcept { return {x.value(), y.value()}; }
			inline vec2<uint16_t> axes_raw_value() const noexcept { return {x.raw_value(), y.raw_value()}; }

			inline std::optional<float> angle_read() noexcept { return angle_update() ? std::optional<float>{angle_value()}: std::optional<float>{std::nullopt}; }
			inline bool angle_update() noexcept { return x.update() + y.update(); }
			inline float angle_value() const noexcept
				{
				auto x_val{x.value()};
				auto y_val{y.value()};
				if(x_val == y_val == 0) { return -1; }

				float dir{std::atan2(y_val, x_val)};
				return std::fmod(dir + angle_right, 360);
				}

			float angle_right{0};

			class calibrator_bounds;
			friend class calibrator_bounds;
			class calibrator_zero;
			friend class calibrator_zero;

		private:
		};

	class joystick::calibrator_bounds
		{
		public:
			calibrator_bounds(joystick& joystick) : x{joystick.x}, y{joystick.y} {}
			inline void calibrate()
				{
				x.calibrate();
				y.calibrate();
				}

		private:
			joystick* joystick_ptr;
			axis::calibrator_bounds x;
			axis::calibrator_bounds y;
		};
	class joystick::calibrator_zero
		{
		public:
			calibrator_zero(joystick& joystick) : x{joystick.x}, y{joystick.y} {}
			inline void calibrate()
				{
				x.calibrate();
				y.calibrate();
				}

		private:
			joystick* joystick_ptr;
			axis::calibrator_zero x;
			axis::calibrator_zero y;
		};
	}