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

			inline std::optional<float> read() noexcept { return update() ? std::optional<float>{value()} : std::optional<float>{std::nullopt}; }
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

			inline float value() { return static_cast<float>(last_value); }

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

			class calibrator;
			friend class calibrator;

			button* up;
			button* dw;
			button* ll;
			button* rr;
		private:
		};
	}