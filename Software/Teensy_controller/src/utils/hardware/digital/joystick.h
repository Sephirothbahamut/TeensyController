#pragma once
#include "button.h"

namespace utils::hardware::digital
	{ 
	// Note: changed and changes detect axes changed without updating the buttons. Use if you're updating the buttons manually from outside before accessing the axis.
	// Otherwise use update/read which will internally update the buttons
	class axis
		{
		public:
			inline axis(button neg, button pos) : neg{neg}, pos{pos} {}

			class calibrator;
			friend class calibrator;

			inline std::optional<float> read   () noexcept { return update () ? std::optional<float>{value()} : std::optional<float>{std::nullopt}; }
			inline std::optional<float> changes() noexcept { return changed() ? std::optional<float>{value()} : std::optional<float>{std::nullopt}; }

			inline bool update() 
				{
				if(neg.update() || pos.update() )
					{
					int value{pos.value() - neg.value()};
					if(value == last_value) { return false; }
					
					last_value = value;
					return true;
					}
				return false;
				}
			inline bool changed() 
				{
				int value{pos.value() - neg.value()};
				if(value == last_value) { return false; }
				
				last_value = value;
				return true;
				}

			inline float value() const noexcept { return static_cast<float>(last_value); }

			button neg;
			button pos;

		private:
			float last_value{0.f};
		};

	class joystick
		{
		public:
			inline joystick(axis x, axis y) : 
				x{x}, y{y},
				up{&this->y.neg}, dw{&this->y.pos}, ll{&this->x.neg}, rr{&this->x.pos}
				 {}

			axis x;
			axis y;

			inline void update()
				{
				x.update();
				y.update();
				}

			inline std::optional<int> angle_read() noexcept { return angle_update() ? std::optional<int>{angle_value()}: std::optional<int>{std::nullopt}; }
			inline bool angle_update() noexcept { return x.update() || y.update(); }
			inline int angle_value() const noexcept
				{
				auto x_val{x.value()};
				auto y_val{y.value()}; 
				int dir
					{
					x_val ==  1 && y_val ==  0 ?   0 :
					x_val ==  1 && y_val == -1 ?  45 :
					x_val ==  0 && y_val == -1 ?  90 :
					x_val == -1 && y_val == -1 ? 135 :
					x_val == -1 && y_val ==  0 ? 180 :
					x_val == -1 && y_val ==  1 ? 225 :
					x_val ==  0 && y_val ==  1 ? 270 :
					x_val ==  1 && y_val ==  1 ? 315 :
					-1
					};
				if(dir != -1) { dir = (dir + angle_right) % 360; }
				return dir;
				}
			int angle_right{0};

			button* up;
			button* dw;
			button* ll;
			button* rr;
		private:
		};
	}