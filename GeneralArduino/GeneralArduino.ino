#include <FastLED.h>
#include <Wire.h>
#include <SPI.h>
#include "REVColorSensor.h"

#define LED_PIN     7
#define NUM_LEDS    40


const int chipSelectPin = 10;
//  D10 (SS), D11 (MOSI), D12 (MISO), D13 (S ...

REVColorSensor sensor = REVColorSensor();

CRGB leds[NUM_LEDS];
int x = 0;
int step = 0;
byte colorValues[3];
int last = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.begin();




  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);





  // set the chipSelectPin as an output:


}

void loop() {
  step += 1;
  if (step == 10)
  {
    step = 0;
  }

  if (Serial.available() > 0)
  {
    x = Serial.read();
  }

  colorValues[0] = sensor.getRed();
  colorValues[1] = sensor.getGreen();
  colorValues[2] = sensor.getBlue();

  Serial.write(colorValues, sizeof(colorValues));


  delay(10);
  // Fill along the length of the strip in various colors
  if (x == 1) {
    for (int i = 0; i < 40; i++){
      
      leds[i] = CRGB::Red;
      leds[i].r /= ((((i+step)%5)*8));
      FastLED.show();
    }
  } else if (x == 2 && last != x) {
    for (int i = 0; i < 40; i++){
      //FastLED.setBrightness((int)(255/(i+step)));
      leds[i] = CRGB::Green;
      leds[i].g /= ((((i+step)%5)*8));
      FastLED.show();
    }
  } else if (x == 3 && last != x) {
    for (int i = 0; i < 40; i++){
      //FastLED.setBrightness((int)(255/(i+step)));
      leds[i] = CRGB::Blue;
      leds[i].b /= ((((i+step)%5)*8));
      FastLED.show();
    }
  } else if (x == 4 && last != x) {
    for (int i = 0; i < 40; i++){
      //FastLED.setBrightness((int)(255/(i+step)));
      leds[i] = CRGB::Yellow;
      leds[i].r /= ((((i+step)%5)*8));
      leds[i].g /= ((((i+step)%5)*8));
      FastLED.show();
    }
  } else if (x == 5 && last != x) {
    for (int i = 0; i < 40; i++){
      //FastLED.setBrightness((int)(255/(i+step)));
      leds[i] = CRGB::White;
      leds[i].r /= ((((i+step)%5)*8));
      leds[i].g /= ((((i+step)%5)*8));
      leds[i].b /= ((((i+step)%5)*8));
      FastLED.show();
    }
  } else if (x == 0){
    rainbow();
  }
  last = x;
}

void rainbow(){
  for (int j = 0; j < 255*4; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(i - (j * 0.5), 255, 255);
    }
    FastLED.show();
  }
}
