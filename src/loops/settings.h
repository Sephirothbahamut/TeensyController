#pragma once
#include "../utils/loop.h"
#include "../utils/hardware/analog/joystick.h"
#include "controller.h"

namespace loops
	{
	class settings : public utils::loop
		{
		public:
			settings() : loop{1} { Serial.println("Entered Settings mode."); }
			~settings() { Serial.println("Exited Settings mode"); }
			
			virtual void step() noexcept final override
				{
				if(controller.dpad.ll->pressed()) { Serial.println("DPAD LEFT"); }
				if(controller.dpad.rr->pressed()) { Serial.println("DPAD RIGHT"); }
				if(controller.dpad.up->pressed()) { Serial.println("DPAD UP"); }
				if(controller.dpad.dw->pressed()) { Serial.println("DPAD DOWN"); }
				if(controller.abxy.ll->pressed()) { Serial.println("ABXY LEFT"); }
				if(controller.abxy.rr->pressed()) { Serial.println("ABXY RIGHT"); }
				if(controller.abxy.up->pressed()) { Serial.println("ABXY UP"); }
				if(controller.abxy.dw->pressed()) { Serial.println("ABXY DOWN"); }

				if(controller.mode_change.pressed()) { running = false; }
				}
		private:
			utils::hardware::analog::joystick::calibrator_zero calibrator_left  {controller.joystick_left};
			utils::hardware::analog::joystick::calibrator_zero calibrator_lright{controller.joystick_left};
		};
	}