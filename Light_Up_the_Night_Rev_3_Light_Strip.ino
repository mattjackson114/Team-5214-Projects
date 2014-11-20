// 11/18/14
//Created by: Matthew Jackson
//Use in accordance with the AndyMark RGB LED Light Strip
#include <FastLED.h>

#define DATA_PIN 3
#define CLOCK_PIN 5
#define NUM_LEDS 80
#define led_brightness 200

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  FastLED.setBrightness(led_brightness);
  FastLED.clear();
  FastLED.showColor(CRGB::Blue);
  delay(225);
  FastLED.clear();
  FastLED.showColor(CRGB::Yellow);
  delay(225);
}

