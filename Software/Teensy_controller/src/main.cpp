#include <Arduino.h>
#include "utils/ui/display.h"
#include "utils/loop.h"
#include "states/main.h"
#include "states/settings.h"
#include "utils/hardware/pin.h"

void setup()
	{
	utils::hardware::pin::analog::init();
	//pinMode(LED_BUILTIN, OUTPUT);
	//digitalWrite(LED_BUILTIN, LOW);
	Serial.begin(9600);
	tft.begin();
	ts.begin();


  pinMode(18, INPUT);
	}
	
utils::state* current_state;

utils::hardware::pin::analog::input anain0{38};
utils::hardware::pin::analog::input anain1{39};
utils::hardware::pin::analog::input anain2{40};
utils::hardware::pin::digital::input anain3{41};
//utils::hardware::pin::digital::input digin{19};


void loop() 
	{
	delay(500);
  //Serial.print(  "A "); Serial.print(anain0.read());
  //Serial.print(", B "); Serial.print(anain1.read());
  Serial.print(", X "); Serial.print(anain2.read());
  Serial.print(", Y "); Serial.print(anain3.read());
  Serial.println();

  return;


	delay(100);
	utils::loop loop{100};

	states::main_joystick     state_main;
	states::settings state_settings;

	current_state = &state_main;

	while(true)
		{
		current_state->enter();
		utils::state* next_state{nullptr};
		switch(static_cast<states::identifier>(loop.run(*current_state)))
			{
			case states::identifier::main    : next_state = &state_main    ; break;
			case states::identifier::settings: next_state = &state_settings; break;
			case states::identifier::calibration_range: next_state = &state_settings; break;
			case states::identifier::calibration_zero : next_state = &state_settings; break;

			default: Serial.println("Encountered error, restarting main loop"); return;
			}
		current_state->leave();
		current_state = next_state;
		}
	}


/*#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2
//XPT2046_Touchscreen ts(CS_PIN);  // Param 2 - NULL - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(38400);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000));
}

boolean wastouched = true;

void loop() {
  boolean istouched = ts.touched();
  if (istouched) {
    TS_Point p = ts.getPoint();
    if (!wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_YELLOW);
      tft.setFont(Arial_60);
      tft.setCursor(60, 80);
      tft.print("Touch");
    }
    tft.fillRect(100, 150, 140, 60, ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
    tft.setFont(Arial_24);
    tft.setCursor(100, 150);
    tft.print("X = ");
    tft.print(p.x);
    tft.setCursor(100, 180);
    tft.print("Y = ");
    tft.print(p.y);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.println(p.y);
  } else {
    if (wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
      tft.setFont(Arial_48);
      tft.setCursor(120, 50);
      tft.print("No");
      tft.setCursor(80, 120);
      tft.print("Touch");
    }
    Serial.println("no touch");
  }
  wastouched = istouched;
  delay(100);
}/**/