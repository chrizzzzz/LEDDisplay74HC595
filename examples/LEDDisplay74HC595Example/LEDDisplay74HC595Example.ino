#include <LEDDisplay74HC595.h>

const int sclkPin = 4;
const int rclkPin = 5;
const int dioPin = 6;

LEDDisplay74HC595 ledDisplay(sclkPin, rclkPin, dioPin);

void setup() {
}

void loop() {
  ledDisplay.refresh(-1.267, 1);

  // Note that delaying will cause the display to flicker,
  // it seems like it can only drive one digit at a time
  // so to display all digits you must continuously loop
  // over the LEDDisplay74HC595::refresh(...) method.
}
