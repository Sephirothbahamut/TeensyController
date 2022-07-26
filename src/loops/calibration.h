#pragma once
#include "../utils/loop.h"
#include "../utils/hardware/analog/joystick.h"
#include "controller.h"

namespace loops
	{
	class calibration_zero : public utils::loop
		{
		public:
			calibration_zero() : loop{1} { }
			
			virtual void step() noexcept final override
				{
				calibrator_left  .calibrate();
				calibrator_lright.calibrate();
				
				if(controller.mode_change.pressed())
					{
					running = false;
					}
				}
		private:
			utils::hardware::analog::joystick::calibrator_zero calibrator_left  {controller.joystick_left};
			utils::hardware::analog::joystick::calibrator_zero calibrator_lright{controller.joystick_left};
		};
	class calibration_bounds : public utils::loop
		{
		public:
			calibration_bounds() : loop{1} { }
			
			virtual void step() noexcept final override
				{
				calibrator_left  .calibrate();
				calibrator_lright.calibrate();
				
				if(controller.mode_change.pressed())
					{
					running = false;
					}
				}
		private:
			utils::hardware::analog::joystick::calibrator_bounds calibrator_left  {controller.joystick_left};
			utils::hardware::analog::joystick::calibrator_bounds calibrator_lright{controller.joystick_left};
		};
	}