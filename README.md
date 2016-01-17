# Arduino Library for a 4-bit LED Digital Tube Module

This is a simple Arduino library for presenting a decimal number on a 4-bit LED Digital Tube Module that uses two 74HC595 shift registers. It's an unknown brand but can be baught on various sites on the net.

# Usage

Put the contents of this repository in a folter named LEDDisplay74HC595 in the Arduino IDE's libraries folter. See the example file reachable when opening a file in the Arduino IDE Open -> libraries -> LEDDisplay74HC595 -> LEDDisplay74HC595Example.

The display uses three digital out pins on your Arduino.

The refresh(number, decimalPlaces) method rounds to specified decimals places, e.g. refresh(1.234, 1) displays as 1.2.

### Example

```
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
```

# No state

The display does not have a state for all digits; this means that you have to refresh the number value continuously in your sketch.

# License

MIT License. See LICENCE.txt.
