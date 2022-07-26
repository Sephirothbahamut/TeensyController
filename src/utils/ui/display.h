#pragma once
#include <Arduino.h>
#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#undef swap

inline constexpr uint8_t CS_PIN{8};
inline constexpr uint8_t TFT_DC{9};
inline constexpr uint8_t TFT_CS{10};
// MOSI=11, MISO=12, SCK=13

inline XPT2046_Touchscreen ts{CS_PIN};
inline constexpr uint8_t TIRQ_PIN{2};
//XPT2046_Touchscreen ts(CS_PIN);  // Param 2 - NULL - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

inline ILI9341_t3 tft{TFT_CS, TFT_DC};

//http://www.barth-dev.de/online/rgb565-color-picker/

union color_t
	{
	inline static constexpr uint16_t max_r{31};
	inline static constexpr uint16_t max_g{63};
	inline static constexpr uint16_t max_b{31};
	inline static constexpr uint16_t as_r(float v) noexcept { return static_cast<uint16_t>(v * max_r); }
	inline static constexpr uint16_t as_g(float v) noexcept { return static_cast<uint16_t>(v * max_g); }
	inline static constexpr uint16_t as_b(float v) noexcept { return static_cast<uint16_t>(v * max_b); }
	inline constexpr void set_r(float f) { r = as_r(f); }
	inline constexpr void set_g(float f) { g = as_g(f); }
	inline constexpr void set_b(float f) { b = as_b(f); }
	
	inline constexpr color_t(uint16_t data) : data{data} {}
	inline constexpr color_t(uint8_t r, uint8_t g, uint8_t b) : r{r}, g{g}, b{b} {}
	inline constexpr color_t(float r, float g, float b) : r{as_r(r)}, g{as_g(g)}, b{as_b(b)} {}

	struct
		{
		uint16_t b : 5;
		uint16_t g : 6;
		uint16_t r : 5;
		};
	uint16_t data;
	inline operator uint16_t() const noexcept { return data; }

	inline static constexpr color_t white  () { return color_t{1.f, 1.f, 1.f}; }
	inline static constexpr color_t black  () { return color_t{0.f, 0.f, 0.f}; }
	inline static constexpr color_t red    () { return color_t{1.f, 0.f, 0.f}; }
	inline static constexpr color_t green  () { return color_t{0.f, 1.f, 0.f}; }
	inline static constexpr color_t blue   () { return color_t{0.f, 0.f, 1.f}; }
	inline static constexpr color_t cyan   () { return color_t{0.f, 1.f, 1.f}; }
	inline static constexpr color_t magenta() { return color_t{1.f, 0.f, 1.f}; }
	inline static constexpr color_t yellow () { return color_t{1.f, 1.f, 0.f}; }

	};