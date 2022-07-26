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
			main() : loop{100} { }
			
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
					/*Serial.println("Entered calibration bounds mode");
					calibration_bounds bounds;
					bounds.run();
					Serial.println("Exited calibration bounds mode");
					Serial.println("Entered calibration zero mode");
					calibration_zero zero;
					zero.run();
					Serial.println("Exited calibration zero mode");*/
					}
				}
		private:
		};
	}