/*
  LEDDisplay74HC595.cpp

  Library for presenting number values using a
  4-Bit LED Digital Tube Module with two 74HC595.

  Created by Chrizzzzz January 2016.

  Released into the public domain.
*/
#include "Arduino.h"
#include "LEDDisplay74HC595.h"

#define NEG_SIGN 10
#define EMPTY 11
#define CHAR_E 12
#define CHAR_R 13

#define MAX_DECIMAL_PLACES 3

const byte CHARS[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01000000, // -
  0b00000000, // <empty>
  0b01111001, // E
  0b01010000, // r
};

const byte POS[] = {
  0b00001000, // first digit in diplay
  0b00000100, // second digit
  0b00000010, // third digit
  0b00000001, // forth digit
};

LEDDisplay74HC595::LEDDisplay74HC595(int sclk, int rclk, int dio)
{
  pinMode(sclk, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(dio, OUTPUT);
  _shiftClock = sclk;
  _resetClock = rclk;
  _displayIO = dio;
  _refreshDigitIndex = 0;
}

void LEDDisplay74HC595::refresh(float number, int decimalPlaces)
{
  boolean isNegative = number < 0;
  boolean hasDecimal = decimalPlaces > 0;
  int decimalPos = MAX_DECIMAL_PLACES - decimalPlaces;
  float absNumber = isNegative ? -number : number;

  // make sure we have a valid decimalPlaces argument
  if(decimalPlaces > MAX_DECIMAL_PLACES || decimalPlaces < 0) {
    setError();
    return;
  }

  // let's move the decimal point out of the number and
  // handle the decimal point separately
  // e.g. 123.45 with one decimal place -> 1235
  int flatNumber = (int)(absNumber * pow(10, decimalPlaces) + 0.5);

  // make sure the display number is not too big to fit in the display
  if((isNegative && flatNumber > 999) || !isNegative && flatNumber > 9999) {
    setError();
    return;
  }

  // build the display values
  byte displayBytes[] {
    CHARS[flatNumber / 1000 % 10],
    CHARS[flatNumber / 100 % 10],
    CHARS[flatNumber / 10 % 10],
    CHARS[flatNumber % 10],
  };

  // remove leading zeroes
  int i = 0;
  while(displayBytes[i] == CHARS[0] && i < decimalPos) {
    displayBytes[i] = CHARS[EMPTY];
    i++;
  }

  // add the neg sign if needed
  if(isNegative) {
    // special case if we have a zero on pos 0 and the decimal point as well,
    // then we use the space of the zero for the neg sign to save space
    if(displayBytes[0] == CHARS[0] && decimalPos == 0) {
      displayBytes[0] = CHARS[NEG_SIGN];
    } else {
      // if not special case, then we simply put the neg sign before the first non-empty display byte
      for(i = 0; i < 4; i++) {
        int prevPos = i - 1;
        // set negative sign before the first digit we encounter
        if(prevPos >= 0 && displayBytes[prevPos] == CHARS[EMPTY] && displayBytes[i] != CHARS[EMPTY]) {
          displayBytes[prevPos] = CHARS[NEG_SIGN];
        }
      }
    }
  }

  // put the decimal sign at the right position
  if(hasDecimal) {
    displayBytes[decimalPos] ^= 0x80; // add decimal point bit at the decimal position
  }

  // set the current digit character to the LED display
  byte digitIndex = _refreshDigitIndex++ % 4;
  setDisplayByte(displayBytes[digitIndex], digitIndex);

}

void LEDDisplay74HC595::setError()
{
  setDisplayByte(CHARS[CHAR_E], 0);
  setDisplayByte(CHARS[CHAR_R], 1);
  setDisplayByte(CHARS[CHAR_R], 2);
}


void LEDDisplay74HC595::setDisplayByte(byte displayByte, int pos)
{
  shiftOut(_displayIO, _shiftClock, MSBFIRST, ~displayByte);
  shiftOut(_displayIO, _shiftClock, MSBFIRST, POS[pos]);
  digitalWrite(_resetClock, LOW);
  digitalWrite(_resetClock, HIGH);
}
