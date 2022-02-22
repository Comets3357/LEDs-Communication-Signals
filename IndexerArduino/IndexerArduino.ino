// Include the required Wire library for I2C<br>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    7 //SUBJECT TO CHANGE IF I COULD BOLD THINGS IN CODE THIS WOULD 100% BE BOLD BUT SERIOUSLY IF IT'S NOT WORKING IT'S PROBABLY THIS
#define LED_COUNT 40 //SUBJECT TO CHANGE IF I COULD BOLD THINGS IN CODE THIS WOULD 100% BE BOLD BUT SERIOUSLY IF IT'S NOT WORKING IT'S PROBABLY THIS

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int LED = 13;
int x = 0;

void setup() {
  Serial.begin(9600);
  
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 1
  Wire.begin(1); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  Wire.setClock(400000);
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
  Serial.println("it worked");
}

void loop() {
  // Fill along the length of the strip in various colors
  if (x == 0) {
    Serial.println("red/blue");
    firstHalfColorWipe(strip.Color(255, 0, 0), 5); // red
    secondHalfColorWipe(strip.Color(0, 0, 255), 5); // blue
  } else if (x == 1) {
    Serial.println("blue/red");
    firstHalfColorWipe(strip.Color(0, 0, 255), 5); // blue
    secondHalfColorWipe(strip.Color(255, 0, 0), 5); // red
  } else if (x == 2) {
    Serial.println("red/black");
    firstHalfColorWipe(strip.Color(255, 0, 0), 5); // red
    secondHalfColorWipe(strip.Color(0, 0, 0), 5); // black (aka off)
  } else if (x == 3) {
    Serial.println("blue/black");
    firstHalfColorWipe(strip.Color(0, 0, 255), 5); // blue
    secondHalfColorWipe(strip.Color(0, 0, 0), 5); // black (aka off)
  } else if (x == 4) {
    Serial.println("black/red");
    firstHalfColorWipe(strip.Color(0, 0, 0), 5); // black (aka off)
    secondHalfColorWipe(strip.Color(255, 0, 0), 5); // red
  } else if (x == 5) {
    Serial.println("black/blue");
    firstHalfColorWipe(strip.Color(0, 0, 0), 5); // black (aka off)
    secondHalfColorWipe(strip.Color(0, 0, 255), 5); // blue
  } else if (x == 6) {
    Serial.println("black/black");
    firstHalfColorWipe(strip.Color(0, 0, 0), 5); // black (aka off)
    secondHalfColorWipe(strip.Color(0, 0, 0), 5); // black (aka off)
  } else if (x == 7) {
    Serial.println("red/red");
    firstHalfColorWipe(strip.Color(255, 0, 0), 5); // red (aka off)
    secondHalfColorWipe(strip.Color(255, 0, 0), 5); // red (aka off)
  } else if (x == 8) {
    Serial.println("blue/blue");
    firstHalfColorWipe(strip.Color(0, 0, 255), 5); // blue (aka off)
    secondHalfColorWipe(strip.Color(0, 0, 255), 5); // blue (aka off)
  }
  receiveEvent(4);
}

void firstHalfColorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels() / 2; i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void secondHalfColorWipe(uint32_t color, int wait) {
  for(int i = strip.numPixels() / 2; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
