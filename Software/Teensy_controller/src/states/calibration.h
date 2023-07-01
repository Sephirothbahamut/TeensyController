#pragma once

#include "general.h"

namespace states
	{
	class calibration_zero : public utils::state
		{
		public:
			virtual void   enter() noexcept final override
				{
				Serial.println("Entered mode: \"Calibration Zero\"");
				redraw();
				start = ::millis();
				};
			virtual void   leave() noexcept final override
				{
				Serial.println("Left    mode: \"Calibration Zero\"");
				};

			virtual size_t step () noexcept final override
				{
				calibrator_left  .calibrate();
				calibrator_lright.calibrate();
				
				if(::millis() - start > 5000) { return static_cast<size_t>(states::identifier::settings); }

				//mode change
				if(controller.mode_change.pressed()) { return static_cast<size_t>(states::identifier::main); }
				return 0;
				}

			void redraw()
				{
				color_t a{0};
				color_t b{0.f, .1f, .5f};
				tft.fillScreenHGradient(a.data, b.data);

				tft.fillRect(8, 24, tft.width() - (8 * 2), tft.height() - (24 * 2), color_t::black());
				tft.drawRect(8, 24, tft.width() - (8 * 2), tft.height() - (24 * 2), color_t::white());

				tft.setCursor(10, 26);
				tft.setTextSize(24);
				tft.println("Calibration Zero");
				tft.setTextSize(14);
				tft.print("Leave your joysticks untouched for 5 seconds.\nThis will calibrate the deadzone.");
				}
			
		private:
			time_t start;
			utils::hardware::analog::joystick::calibrator_zero calibrator_left  {controller.joystick_left};
			utils::hardware::analog::joystick::calibrator_zero calibrator_lright{controller.joystick_left};
		};
	class calibration_bounds : public utils::state
		{
		public:
			virtual void   enter() noexcept final override
				{
				Serial.println("Entered mode: \"Calibration Bounds\"");
				redraw();
				};
			virtual void   leave() noexcept final override
				{
				Serial.println("Left    mode: \"Calibration Bounds\"");
				};

			virtual size_t step () noexcept final override
				{
				calibrator_left  .calibrate();
				calibrator_lright.calibrate();
				
				if(controller.abxy.rr->pressed() + controller.abxy.up->pressed() + controller.abxy.ll->pressed() + controller.abxy.dw->pressed()) { return static_cast<size_t>(states::identifier::settings); }

				//mode change
				if(controller.mode_change.pressed()) { return static_cast<size_t>(states::identifier::main); }
				return 0;
				}

			void redraw()
				{
				color_t a{0};
				color_t b{0.f, .1f, .5f};
				tft.fillScreenHGradient(a.data, b.data);

				tft.fillRect(8, 24, tft.width() - (8 * 2), tft.height() - (24 * 2), color_t::black());
				tft.drawRect(8, 24, tft.width() - (8 * 2), tft.height() - (24 * 2), color_t::white());

				tft.setCursor(10, 26);
				tft.setTextSize(24);
				tft.println("Calibration Zero");
				tft.setTextSize(14);
				tft.print("Rotate both joysticks the widest you can,\nthen press any button in the\nright cluster to finalize.");
				}
			
		private:
			utils::hardware::analog::joystick::calibrator_bounds calibrator_left  {controller.joystick_left};
			utils::hardware::analog::joystick::calibrator_bounds calibrator_lright{controller.joystick_left};
		};
	}