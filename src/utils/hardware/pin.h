#pragma once
#include <Arduino.h>
#include <cstdint>

namespace utils::hardware
	{
	class pin
		{
		public:
			inline pin(uint8_t index) : _index{index} {}
			inline uint8_t index() const noexcept { return _index; }
			
			struct digital;
			struct analog;
		private:
			uint8_t _index;
		};

	struct pin::digital : pin
		{
		using pin::pin;
		struct input;
		struct input_pullup;
		struct output;
		};
		
	struct pin::digital::input : pin::digital
		{
		inline input(uint8_t index) : pin::digital{index} { pinMode(pin::digital::index(), INPUT); }
		inline bool read() const noexcept { return digitalRead(index()) == HIGH; }
		};
	struct pin::digital::input_pullup : pin::digital
		{
		inline input_pullup(uint8_t index) : pin::digital{index} { pinMode(pin::digital::index(), INPUT_PULLUP); }
		inline bool read() const noexcept { return digitalRead(index()) == HIGH; }
		};

	struct pin::digital::output : pin::digital
		{
		output(uint8_t index) : pin::digital{index} { pinMode(pin::digital::index(), OUTPUT); }
		inline void write(bool state) const noexcept { digitalWrite(index(), state ? HIGH : LOW); }
		inline void high() const noexcept { write(true ); }
		inline void low () const noexcept { write(false); }
		struct stateful;
		};
		
	class pin::digital::output::stateful : public pin::digital::output
		{
		public:
			using pin::digital::output::output;
			inline void write(bool state) noexcept { pin::digital::output::write(state); _state = state; }
			inline void high() noexcept { write(true ); }
			inline void low () noexcept { write(false); }   
			inline void toggle() { write(!state()); }

			inline uint8_t state() const noexcept { return _state; }

		private:
			bool _state{false};
		};
		
	struct pin::analog : pin
		{
		inline static constexpr uint8_t resolution{12};
		inline static constexpr uint16_t max{static_cast<uint16_t>(std::pow(2, resolution)) - 1};
		inline static void init()
			{
			//analogReadAveraging(16);
			analogReadResolution(resolution);
			}

		using pin::pin;
		struct input;
		struct output;
		};

	struct pin::analog::input : pin::analog
		{
		inline input(uint8_t index) : pin::analog{index} { pinMode(pin::analog::index(), INPUT); }
		inline uint16_t read() const noexcept { return analogRead(index()); }
		};

	struct pin::analog::output : pin::analog
		{
		inline output(uint8_t index) : pin::analog{index} { pinMode(pin::analog::index(), OUTPUT); }
		inline void write(uint16_t value) const noexcept { analogWrite(index(), value); }
		struct stateful;
		};
		
	class pin::analog::output::stateful : public pin::analog::output
		{
		public:
			using pin::analog::output::output;
			inline void write(bool value) noexcept { pin::analog::output::write(value); _value = value; }
			inline void high() noexcept { write(pin::analog::max); }
			inline void low () noexcept { write(0); }   
			inline void toggle() { write(value() ? 0 : pin::analog::max); }

			inline uint8_t value() const noexcept { return _value; }

		private:
			uint16_t _value{0};
		};
	}