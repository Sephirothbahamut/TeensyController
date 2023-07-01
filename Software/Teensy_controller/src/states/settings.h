#pragma once

#include <array>

#include "../utils/ui/layer.h"

#include "general.h"

namespace states
	{
	class settings : public utils::state
		{
		public:
			virtual void   enter() noexcept final override
				{
				Serial.println("Entered mode: \"Settings\"");
				redraw();
				};
			virtual void   leave() noexcept final override
				{
				Serial.println("Left    mode: \"Settings\"");
				};

			virtual size_t step (utils::time_t delta_time) noexcept final override
				{

				if(controller.dpad.up->pressed()) { layer.prev(); }
				if(controller.dpad.dw->pressed()) { layer.next(); }

				if(controller.abxy.dw->pressed() + controller.dpad.ll->pressed()) //+ instead of || guarantees non-lazy evaluation
					{ layer.back(); }
				if(controller.abxy.rr->pressed() + controller.dpad.rr->pressed()) //+ instead of || guarantees non-lazy evaluation
					{
					if(auto out{layer.click()})
						{
						switch(out.value())
							{
							case layer_id::calibration_range: return static_cast<size_t>(states::identifier::calibration_range);
							case layer_id::calibration_zero : return static_cast<size_t>(states::identifier::calibration_zero );
							}
						redraw();
						}
					}

				//mode change
				if(controller.mode_change.pressed()) { return static_cast<size_t>(states::identifier::main); }
				return 0;
				};
				
		private:
			inline void redraw() const noexcept
				{
				color_t a{0};
				color_t b{0.f, .1f, .5f};
				tft.fillScreenHGradient(a.data, b.data);

				layer.draw();
				}

			enum layer_id { calibration, mapping, calibration_zero, calibration_range };

			layer layer
				{
				"Settings",
					{
					//Root begin
					layer::slot_t{.label{"Calibration"},                                 .first{layer_id::calibration     }, .submenu{true }, .out{layer_id::calibration_zero } },
					layer::slot_t{.label{"Mapping"    },                                 .first{layer_id::mapping         }, .submenu{false}, .out{layer_id::mapping          } },
					//Root end
					//Calibration submenu begin
					layer::slot_t{.label{"Zero"       }, .source{layer_id::calibration}, .first{layer_id::calibration_zero}, .submenu{false}, .out{layer_id::calibration_zero } },
					layer::slot_t{.label{"Range"      }, .source{layer_id::calibration}, .first{layer_id::calibration_zero}, .submenu{false}, .out{layer_id::calibration_range} },
					//Calibration submenu end
					}
				};
		};
	}