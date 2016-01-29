/*
  LEDDisplay74HC595.h

  Library for presenting number values using a
  4-Bit LED Digital Tube Module with two 74HC595.

  Created by Chrizzzzz January 2016.

  Released into the public domain.
*/
#ifndef LEDDisplay74HC595_h
#define LEDDisplay74HC595_h

#include "Arduino.h"

class LEDDisplay74HC595
{
public:
  LEDDisplay74HC595(int sclk, int rclk, int dio);
  void refresh(float number, int decimalPlaces);
private:
  int _shiftClock;
  int _resetClock;
  int _displayIO;
  byte _refreshDigitIndex;
  void setError();
  void setDisplayByte(byte displayByte, int pos);
};

#endif