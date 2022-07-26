#pragma once
#include "../utils/loop.h"
#include "../utils/hardware/analog/joystick.h"
#include "../controller.h"

#include "settings.h"

namespace loops
	{
	class main : public utils::loop
		{
		public:
			inline main() : loop{100} { redraw(); }
			
			inline void redraw()
				{
				color_t a{0};
				color_t b{0.f, .1f, .5f};
				tft.fillScreenVGradient(a.data, b.data);
				}

			virtual void step() noexcept final override
				{
				//debug
				//if(auto reading{controller.joystick_left .x.read()}) { Serial.print("controller.joystick_left .x = "); Serial.println(reading.value()); }
				//if(auto reading{controller.joystick_left .y.read()}) { Serial.print("controller.joystick_left .y = "); Serial.println(reading.value()); }
				//if(auto reading{controller.joystick_right.x.read()}) { Serial.print("controller.joystick_right.x = "); Serial.println(reading.value()); }
				//if(auto reading{controller.joystick_right.y.read()}) { Serial.print("controller.joystick_right.y = "); Serial.println(reading.value()); }

				//mode change
				if(controller.mode_change.pressed())
					{
					settings settings;
					settings.run();
					redraw();
					}
				}
		private:
		};
	}