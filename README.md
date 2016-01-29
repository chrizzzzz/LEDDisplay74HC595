# Arduino Library for a 4-bit LED Digital Tube Module

This is a simple Arduino library for presenting a decimal number on a 4-bit LED Digital Tube Module that uses two 74HC595 shift registers. It's an unknown brand but can be bought on various sites on the net.

# Usage

Put the contents of this repository in a folder named LEDDisplay74HC595 in the Arduino IDE's libraries folder. See the example file by opening it in the Arduino IDE: Open -> libraries -> LEDDisplay74HC595 -> LEDDisplay74HC595Example.

The display uses three digital out pins on your Arduino.

The refresh(number, decimalPlaces) method rounds to specified decimals places, e.g. refresh(1.234, 1) displays as 1.2.

#### Example

```C++
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

A tip is to use timer interrupts to drive the display to avoid flicker when you need to process other stuff as well.

#### Example
```C++
#include <TimerOne.h>
//...
void setup() {
  //...
  Timer1.initialize(5000);
  Timer1.attachInterrupt(refreshDisplay);
}
void refreshDisplay() {
  ledDisplay.refresh(myValue, 1);
}
```

# License

MIT License. See LICENCE.txt.
