/*Created by: Matthew Jackson
 FRC Team 5214
 12/18/2014
 Used to control LED light strip on robot
 LED strip from AndyMark
 */
#include <FastLED.h>
#define DATA_PIN 3
#define CLOCK_PIN 5
#define NUM_LEDS 80
#define led_brightness 255
int input = 0;
int ledPin = 13;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  FastLED.clear();
  FastLED.setBrightness(led_brightness);
  while (Serial.available() > 0) {
    digitalWrite(ledPin, LOW);
    input = Serial.read();
    if (input == 'R') {
      FastLED.clear();
      FastLED.showColor(CRGB::Red);
    }
    else if (input == 'B') {
      FastLED.clear();
      FastLED.showColor(CRGB::Blue);
    }
    else if (input == 'O') {
      FastLED.showColor(CRGB(0, 0, 0));
    }
    else if (input == 'S') { //South Lake Mode
      for(int led = 0; led <= 40; led++) {
        leds[led] = CRGB::Blue;
      } 
            for(int led = 41; led <= 80; led++) {
        leds[led] = (CRGB(255, 132, 0));
      } 
      FastLED.show();
    }
    else if (input == 'C') { //Christmas Mode
      for(int led = 0; led <= 40; led++) {
        leds[led] = CRGB::Red;
      } 
       for(int led = 41; led <= 80; led++) {
        leds[led] = CRGB::Green;
      }      
      FastLED.show();
    }
    else if (input == 'P') { //Patriotic Mode
      for (int led = 0; led <= 26; led++) {
        leds[led] = CRGB::Blue;
      }
      for (int led = 27; led <= 51; led++) {
        leds[led] = CRGB::Red;
      }
      for (int led = 52; led <= 80; led++) {
        leds[led] = (CRGB(255, 255, 210));
      }
      FastLED.show();
    }
    else if (input == 'H') { //Halloween Mode
      for (int led = 0; led <= 40; led++) {
        leds[led] = (CRGB(255, 62, 0));
      }
      for (int led = 40; led <= 80; led++) {
        leds[led] = (CRGB(255, 132, 0));
      }
      FastLED.show();
    }
    else if (input == 'T') {

      for (int led = 0; led <= 26; led++) {
        leds[led] = (CRGB(255, 62, 0));
      }
      for (int led = 27; led <= 53; led++) {
        leds[led] = (CRGB(255, 0, 0));
      }
      //255, 132
      for (int led = 54; led <= 80; led++) {
        leds[led] = (CRGB(255, 132, 0));
      }
      FastLED.show();
    }
    Serial.flush(); //Without this the lights would not stay on permanentley
  }
}

