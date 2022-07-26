#pragma once

#include <array>

#include "../utils/loop.h"
#include "../utils/hardware/analog/joystick.h"
#include "controller.h"

#include "../utils/ui/layer.h"

namespace loops
	{
	class settings : public utils::loop
		{
		public:
			inline settings() : loop{1} 
				{
				Serial.println("Entered Settings mode."); 

				color_t a{0};
				color_t b{0.f, .1f, .5f};
				tft.fillScreenHGradient(a.data, b.data);

				layer.draw();
				}
			inline ~settings() { Serial.println("Exited Settings mode"); }
			
			inline virtual void step() noexcept final override
				{
				if(controller.dpad.ll->pressed()) { Serial.println("DPAD LEFT"); }
				if(controller.dpad.rr->pressed()) { Serial.println("DPAD RIGHT"); }
				if(controller.dpad.up->pressed()) { layer.prev(); Serial.println("DPAD UP"); }
				if(controller.dpad.dw->pressed()) { layer.next(); Serial.println("DPAD DOWN"); }
				if(controller.abxy.ll->pressed()) { Serial.println("ABXY LEFT"); }
				if(controller.abxy.rr->pressed()) { Serial.println("ABXY RIGHT"); }
				if(controller.abxy.up->pressed()) { Serial.println("ABXY UP"); }
				if(controller.abxy.dw->pressed()) { Serial.println("ABXY DOWN"); }

				if(controller.abxy.rr->pressed()) 
					{
					switch(current_layer().get_current())
						{
						
						}
					}

				if(controller.mode_change.pressed()) { running = false; }
				}
		private:
			utils::hardware::analog::joystick::calibrator_zero calibrator_left  {controller.joystick_left};
			utils::hardware::analog::joystick::calibrator_zero calibrator_lright{controller.joystick_left};

			enum layer_id_t{ root = 0, calibration };
			layer_id_t current_index{layer_id_t::root};
			layer& current_layer()  { return layers[current_index]; }

			std::array<layer, 2> layers
				{
					layer{"Settings", {"Calibration", "Mapping", "rtyu"}},
					layer{"Settings > Calibration", {"Zero", "Edges"}}
				};
		};
	}