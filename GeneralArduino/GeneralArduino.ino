#include <FastLED.h>
#include <Wire.h>

#define LED_PIN     4
#define NUM_LEDS    40

CRGB leds[NUM_LEDS];
int x = 0;

void setup() {
  Serial.begin(9600);
  
  // Start the I2C Bus as Slave on address 1
  Wire.begin(1); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  Wire.setClock(400000);
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}

void loop() {
  // Fill along the length of the strip in various colors
  if (x == 1) {
    Serial.println("red");
    for (int i = 0; i < 40; i++){
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(5);
    }
  } else if (x == 2) {
    Serial.println("green");
    for (int i = 0; i < 40; i++){
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(5);
    }
  } else if (x == 3) {
    Serial.println("blue");
    for (int i = 0; i < 40; i++){
      leds[i] = CRGB::Blue;
      FastLED.show();
      delay(5);
    }
  } else if (x == 4) {
    Serial.println("yellow");
    for (int i = 0; i < 40; i++){
      leds[i] = CRGB::Yellow;
      FastLED.show();
      delay(5);
    }
  } else if (x == 5) {
    Serial.println("white");
    for (int i = 0; i < 40; i++){
      leds[i] = CRGB::White;
      FastLED.show();
      delay(5);
    }
  } else {
    rainbow();
  }
  receiveEvent(4);
}

void rainbow(){
  for (int i = 0; i < 40; i++){
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(50);
  }
  for (int i = 39; i >= 0; i--){
    leds[i] = CRGB::Orange;
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < 40; i++){
    leds[i] = CRGB::Yellow;
    FastLED.show();
    delay(50);
  }
  for (int i = 39; i >= 0; i--){
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < 40; i++){
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(50);
  }
  for (int i = 39; i >= 0; i--){
    leds[i] = CRGB::Purple;
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < 40; i++){
    leds[i] = CRGB::White;
    FastLED.show();
    delay(50);
  }
  delay(500);
}
