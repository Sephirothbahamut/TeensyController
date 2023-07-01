#pragma once

#include "general.h"
#include <Arduino.h>
//#include <usb_joystick.h>
//#include <Mouse.h>
//#include <Keyboard.h>

namespace states
	{
	class main_joystick : public utils::state
		{
		public:
			
			virtual void   enter() noexcept final override
				{
				Serial.println("Entered mode: \"Main Joystick\"");
				redraw();
				
				Joystick.useManualSend(true);
				Joystick.begin();
				};
			virtual void   leave() noexcept final override
				{
				Serial.println("Left    mode: \"Main Joystick\"");

				Joystick.end();
				};
			virtual size_t step (utils::time_t delta_time) noexcept final override
				{

				controller.dpad.update();
				Joystick.hat(controller.dpad.angle_value()); 

				controller.abxy.update();
				Joystick.button(1, controller.abxy.rr->value());
				Joystick.button(2, controller.abxy.up->value());
				Joystick.button(3, controller.abxy.ll->value());
				Joystick.button(4, controller.abxy.dw->value());


				tft.drawPixel(3, 10, controller.abxy.rr->value() ? color_t::white() : color_t::black());
				tft.drawPixel(2,  9, controller.abxy.up->value() ? color_t::white() : color_t::black());
				tft.drawPixel(1, 10, controller.abxy.ll->value() ? color_t::white() : color_t::black());
				tft.drawPixel(2, 11, controller.abxy.dw->value() ? color_t::white() : color_t::black());

				controller.joystick_left.update();
				Joystick.button(11, controller.joystick_left.button.value());

				auto lx{controller.joystick_left .x.value()};
				auto ly{controller.joystick_left .y.value()};
				auto rx{controller.joystick_right.x.value()};
				auto ry{controller.joystick_right.y.value()};

				Serial.print(lx); Serial.print(", "); Serial.print  (ly); Serial.print(" | ");
				Serial.print(rx); Serial.print(", "); Serial.println(ry);
				Joystick.X(rx);
				Joystick.Y(ry);
				
				controller.joystick_right.update();
				Joystick.button(12, controller.joystick_right.button.value());
				Joystick.Z      (rx);
				Joystick.Zrotate(ry);
				
				Joystick.send_now();

				//mode change
				if(controller.mode_change.pressed()) { return static_cast<size_t>(states::identifier::settings); }

				return 0;
				};

			inline void redraw()
				{
				color_t a{0};
				color_t b{0.f, .1f, .5f};
				tft.fillScreenVGradient(a.data, b.data);
				}

		private:
		};
		
	class main_mouse : public utils::state
		{
		public:
			
			virtual void   enter() noexcept final override
				{
				Serial.println("Entered mode: \"Main Mouse\"");
				redraw();
				
				Mouse.begin();
				};
			virtual void   leave() noexcept final override
				{
				Serial.println("Left    mode: \"Main Mouse\"");

				Mouse.end();
				};
			virtual size_t step (utils::time_t delta_time) noexcept final override
				{
				controller.joystick_left .axes_update();
				controller.joystick_right.axes_update();

				float speed = pixels_per_second * (delta_time / 1000.f);
				Mouse.move(controller.joystick_left .x.value() * speed, controller.joystick_left .y.value() * speed, controller.joystick_right.x.value() * speed, controller.joystick_right.y.value() * speed);
				Mouse.set_buttons
					(
					controller.abxy.rr->value(),
					controller.joystick_right.button.value(),
					controller.abxy.up->value(),
					controller.abxy.dw->value(),
					controller.abxy.ll->value()
					);
					tft.fillCircle(100, 100, 64, color_t::black());
					tft.drawCircle(100, 100, 64, color_t::red());
					tft.drawLine  (100, 100, 100 + controller.joystick_left .x.value() * 100, 100 + controller.joystick_left .y.value() * 100, color_t::red());
					
				//mode change
				if(controller.mode_change.pressed()) { return static_cast<size_t>(states::identifier::settings); }

				return 0;
				};

			inline void redraw()
				{
				color_t a{0};
				color_t b{0.f, .1f, .5f};
				tft.fillScreenVGradient(a.data, b.data);
				}

			float pixels_per_second{100};
		private:
		};
	}