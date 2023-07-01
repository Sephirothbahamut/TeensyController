#pragma once

#include "display.h"
#include "utils/hardware/analog/joystick.h"
#include "utils/hardware/digital/button.h"
#include "utils/hardware/digital/joystick.h"

namespace utils::ui::hardware_drawers
	{
	class analog_joystick
		{
		public:
			analog_joystick(vec2<int> position, vec2<int> size, const hardware::analog::joystick& joystick) : 
				position{position}, size{size}, 
				center{position.x + (size.x / 2), position.y + (size.y / 2)},
				joystick{&joystick} 
				{} 

			void step() const noexcept
				{
				tft.fillCircle(center.x, center.y, radius, color_t::black());
				tft.fillCircle(center.x, center.y, 2, color_t::black());

				tft.drawLine(center.x, center.y, joystick->x.value(), joystick->y.value(), color_t::white());

				tft.drawCircle(center.x, center.y, radius, joystick->button.value() ? color_t::green() : color_t::red());
				}
		private:
			vec2<int> position;
			vec2<int> size;
			vec2<int> center;
			int radius{std::min(size.x, size.y) / 2};
			const hardware::analog::joystick* joystick;
		};
	class digital_joystick
		{
		public:
			digital_joystick(vec2<int> position, vec2<int> size, const hardware::digital::joystick& joystick) : 
				position{position}, size{size}, 
				center{position.x + (size.x / 2), position.y + (size.y / 2)},
				joystick{&joystick} 
				{} 

			void step() const noexcept
				{
					//TODO
				}
		private:
			vec2<int> position;
			vec2<int> size;
			vec2<int> center;
			int radius{std::min(size.x, size.y) / 2};
			const hardware::digital::joystick* joystick;
		};
	}