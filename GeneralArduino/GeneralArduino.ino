
#include <FastLED.h> 
#include <Wire.h> 
#include <SPI.h> 
#include "REVColorSensor.h" 
 
#define LED_PIN     4 
#define NUM_LEDS    40 
 
 
const int chipSelectPin = 10; 
//  D10 (SS), D11 (MOSI), D12 (MISO), D13 (S ... 
 
REVColorSensor sensor = REVColorSensor(); 
 
CRGB leds[NUM_LEDS]; 
byte color[1];
int x = 0; 
int step = 0; 
byte colorValues[3]; 
int last = 10; 

void writeColor()
{
  if (sensor.getRed() > 350 && sensor.getBlue() < 200)
  {
    color[0] = 0x0C;
  } else if (sensor.getRed() < 200 && sensor.getBlue() > 350)
  {
    color[0] = 0x0B;
  } else 
  {
    color[0] = 0x0A;
  }

  char colr[1];
  colr[0] = 1;

  Serial.write(color, 1);
}
 
void setup() { 
  Serial.begin(9600); 
  Wire.begin(); 
  sensor.begin(); 
 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); 
  FastLED.setBrightness(255); 
} 
 
void loop() { 
  step++; 
   
  if (step == 10){ 
    step = 0; 
  } 
 
  if (Serial.available() > 0){ 
    x = Serial.read(); 
  } 
 
  writeColor();
//  Serial.println(String(sensor.getRed())); 
 
  delay(1); 
  // Fill along the length of the strip in various colors 
  if (x == 1) { 
    for (int i = 0; i < 40; i++){ 
       
      leds[i] = CRGB::Red; 
      FastLED.show(); 
    } 
  } else if (x == 2 && last != 2) { 
    for (int i = 0; i < 40; i++){ 
      //FastLED.setBrightness((int)(255/(i+step))); 
      leds[i] = CRGB::Green; 
      FastLED.show(); 
    } 
  } else if (x == 3 && last != 3) { 
    for (int i = 0; i < 40; i++){ 
      //FastLED.setBrightness((int)(255/(i+step))); 
      leds[i] = CRGB::Blue; 
      FastLED.show(); 
    } 
  } else if (x == 4 && last != 4) { 
    for (int i = 0; i < 40; i++){ 
      //FastLED.setBrightness((int)(255/(i+step))); 
      leds[i] = CRGB::Yellow; 
      FastLED.show(); 
    } 
  } else if (x == 5 && last != 5) { 
    for (int i = 0; i < 40; i++){ 
      //FastLED.setBrightness((int)(255/(i+step))); 
      leds[i] = CRGB::White; 
      FastLED.show(); 
    } 
  } else if (x == 0 && last != 0){ 
    for (int i = 0; i < 40; i++){ 
      //FastLED.setBrightness((int)(255/(i+step))); 
      leds[i].r = 255;
      leds[i].b = 0;
      leds[i].g = 10;
      FastLED.show(); 
    } 
  } 
  last = x; 
} 
 

 
