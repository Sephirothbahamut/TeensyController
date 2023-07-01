#pragma once

#include "../utils/state.h"
#include "../utils/hardware/analog/joystick.h"
#include "../controller.h"
#include "../utils/UI/display.h"

namespace states
	{
	enum class identifier : size_t { main = 1, settings, calibration_zero, calibration_range };	
	}