#pragma once
#include <initializer_list>
#include <vector>//TODO static vector
#include "display.h"

class layer
	{
	public:
		struct slot_t
			{
			const char* label;
			size_t source{-1};
			size_t first;
			bool submenu;
			size_t out;
			};

		layer(const char* title, std::initializer_list<slot_t> slots = {}) : title{title}, slots(slots) {}
		layer() = default;

		inline void draw() const noexcept
			{
			color_t a{0};
			color_t b{0.f, .1f, .5f};
			tft.fillScreenHGradient(a.data, b.data);

			tft.setTextColor(ILI9341_WHITE);
			tft.setFont(Arial_10);
			tft.setCursor(2, 2);

			tft.print(title);
			size_t tmp_index{current_index};
			while(slot_at(tmp_index).source != size_t{-1})
				{
				tmp_index = slot_at(tmp_index).source;
				tft.print(slot_at(tmp_index).label);
				tft.print("/");
				}
			
			tft.setFont(Arial_12);
			
			size_t ui_index{0};
			const auto& current_slot{slot_at(current_index)};
			size_t index{current_slot.first};
			while(true)
				{
				const auto& slot{slot_at(index)};
				if(slot.source != current_slot.source) { break; }


				draw_label(ui_index, slot.label);
				draw_arrow(ui_index, index == current_index);
				ui_index++;
				index++;
				}
			}
		
		inline void next() 
			{
			size_t next_index{current_index + 1};
			Serial.print("going to"); Serial.println(next_index);
			if(next_index == slots.size()) { Serial.println("out of bounds"); return; }
			if(slot_at(next_index).source != slot_at(current_index).source) { Serial.println("out of section"); return; }
			select(current_index + 1);
			}
		inline void prev() 
			{
			size_t prev_index{current_index - 1};
			Serial.print("going to"); Serial.println(prev_index);
			if(current_index == 0) { Serial.println("out of bounds"); return; }
			if(slot_at(prev_index).source != slot_at(current_index).source) { Serial.println("out of section"); return; }
			select(current_index - 1);
			}
		inline std::optional<size_t> click()
			{
			const auto& current{slot_at(current_index)};
			Serial.print("Clicking at "); Serial.print(current_index); Serial.print(": "); Serial.println(current.label);
			if(current.submenu)
				{
				current_index = current.out;
				draw();
				Serial.print("Entering subsection at "); Serial.print(current_index); Serial.print(": "); Serial.println(current.label);
				return std::nullopt;
				}
			else { Serial.print("Outputting value "); Serial.println(current.out); return current.out; }
			}
		inline void back()
			{
			const auto& current{slot_at(current_index)};
			if(current.source != size_t{-1})
				{
				current_index = current.source;
				draw();
				Serial.print("Exiting subsection at "); Serial.print(current_index); Serial.print(": "); Serial.println(current.label);
				}
			}

		std::vector<slot_t> slots;
	private:
		const char* title;

		size_t current_index{0};

		const slot_t& slot_at(size_t index) const noexcept { return slots[index]; }
		const size_t get_ui_index(size_t index) { return index - slot_at(index).first; }
		inline void select(size_t index) 
			{
			//if(index >= slots.size()) { index = 0; }
			draw_arrow(get_ui_index(current_index), false);
			current_index = index;
			draw_arrow(get_ui_index(current_index), true);
			Serial.print("went to "); Serial.print(current_index); Serial.print(": "); Serial.println(slot_at(current_index).label);
			}

		inline static constexpr int16_t base_y      {20};
		inline static constexpr int16_t base_x      { 5};
		inline static constexpr int16_t arrow_width {16};
		inline static constexpr int16_t text_padding{ 4};
		inline static constexpr int16_t text_height {12};
		

		inline void draw_arrow(size_t ui_index, bool highlighted) const noexcept
			{
			tft.fillTriangle
				(
				base_x              , base_y + ( ui_index      * (text_padding + text_height + text_padding)) + text_padding,
				base_x + arrow_width, base_y + ( ui_index      * (text_padding + text_height + text_padding)) + text_padding + (text_height / 2),
				base_x              , base_y + ((ui_index + 1) * (text_padding + text_height + text_padding)) - text_padding,
				highlighted ? color_t::white() : color_t::red()//color_t{0.f, .5f, 1.f}
				);
			tft.drawTriangle
				(
				base_x              , base_y + ( ui_index      * (text_padding + text_height + text_padding)) + text_padding,
				base_x + arrow_width, base_y + ( ui_index      * (text_padding + text_height + text_padding)) + text_padding + (text_height / 2),
				base_x              , base_y + ((ui_index + 1) * (text_padding + text_height + text_padding)) - text_padding,
				color_t::white().data
				);
			}
		inline void draw_label(size_t ui_index, const char* label) const noexcept
			{
			tft.setCursor(base_x + arrow_width + text_padding, base_y + (ui_index * (text_height + (text_padding * 2))) + text_padding);
			tft.print(label);
			}
	};