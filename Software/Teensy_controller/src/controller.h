#pragma once

#include "utils/hardware/digital/button.h"
#include "utils/hardware/digital/joystick.h"
#include "utils/hardware/analog/joystick.h"

class controller_t
	{
	public:
		utils::hardware::analog::joystick joystick_left {A0, A1, 7};
		utils::hardware::analog::joystick joystick_right{A3, A2, 6};
		utils::hardware::digital::joystick dpad         {utils::hardware::digital::axis{34, 33}, utils::hardware::digital::axis{37, 36}};
		utils::hardware::digital::joystick abxy         {utils::hardware::digital::axis{32, 31}, utils::hardware::digital::axis{28, 29}};

		utils::hardware::digital::axis shoulder_up {3, 4};
		utils::hardware::digital::button start{10};
		utils::hardware::digital::button select{11};
		utils::hardware::digital::button mode_change{0};
	} controller;