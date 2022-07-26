#pragma once
#include <initializer_list>
#include <vector>//TODO static vector
#include "display.h"

class layer
	{
	public:
		layer(const char* title, std::initializer_list<const char*> labels) : title{title}, labels(labels) {}

		inline void draw() const noexcept
			{
			tft.setTextColor(ILI9341_WHITE);
			tft.setFont(Arial_10);
			tft.setCursor(2, 2);
			tft.print(title);
			
			tft.setFont(Arial_12);
			for (size_t i = 0; i < labels.size(); i++)
				{
				draw_label(i);
				draw_border(i, i == current);
				}
			}

		inline void select(size_t index) 
			{
			if(index != current) 
				{
				if(index >= labels.size()) { index = 0; }
				draw_border(current, false);
				draw_border(index  , true);
				current = index;
				}
			}
		inline void next() { if(current < labels.size() - 1) { select(current + 1); } }
		inline void prev() { if(current > 0                ) { select(current - 1); } }

		inline size_t get_current() const noexcept { return current; }
	private:
		const char* title;
		std::vector<const char*> labels;
		size_t current{0};
		inline static constexpr int16_t base_y      {20};
		inline static constexpr int16_t base_x      { 5};
		inline static constexpr int16_t arrow_width {16};
		inline static constexpr int16_t text_padding{ 4};
		inline static constexpr int16_t text_height {12};
		

		inline void draw_border(size_t index, bool highlighted) const noexcept
			{
			tft.fillTriangle
				(
				base_x              , base_y + ( index      * (text_padding + text_height + text_padding)) + text_padding,
				base_x + arrow_width, base_y + ( index      * (text_padding + text_height + text_padding)) + text_padding + (text_height / 2),
				base_x              , base_y + ((index + 1) * (text_padding + text_height + text_padding)) - text_padding,
				highlighted ? color_t::white() : color_t{0.f, .5f, 1.f}
				);
			tft.drawTriangle
				(
				base_x              , base_y + ( index      * (text_padding + text_height + text_padding)) + text_padding,
				base_x + arrow_width, base_y + ( index      * (text_padding + text_height + text_padding)) + text_padding + (text_height / 2),
				base_x              , base_y + ((index + 1) * (text_padding + text_height + text_padding)) - text_padding,
				color_t::white().data
				);
			}
		inline void draw_label(size_t index) const noexcept
			{
			tft.setCursor(base_x + arrow_width + text_padding, base_y + (index * (text_height + (text_padding * 2))) + text_padding);
			tft.print(labels[index]);
			}
	};