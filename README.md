# Arduino Library for a 4-bit LED Digital Tube Module

This is a simple Arduino library for presenting a decimal number on a 4-bit LED Digital Tube Module that uses two 74HC595 shift registers. It's an unknown brand but can be baught on various sites on the net.

# Usage

Put the contents of this repository in a folter named LEDDisplay74HC595 in the Arduino IDE's libraries folter. See the example file reachable when opening a file in the Arduino IDE Open -> libraries -> LEDDisplay74HC595 -> LEDDisplay74HC595Example.

# No state

The display does not have a state for all digits; this means that you have to refresh the number value continuously in your sketch.

# License

MIT License. See [LICENCE.txt](LICENCE.txt).
