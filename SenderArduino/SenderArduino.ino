// Include the required Wire library for I2C<br>
#include <Wire.h>
int x = 0;
void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
}
void loop() {
  Wire.beginTransmission(1); // transmit to device #1
  Wire.write(x);              // sends x 
  Wire.endTransmission();    // stop transmitting
  x++; // Increment x
  if (x == 6){
    x = 0; // reset x once it gets 6
  }
  delay(5000);
}
