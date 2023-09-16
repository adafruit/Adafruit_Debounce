/*!
 * @file Adafruit_Debounce.h
 *
 * @mainpage Adafruit Button Debounce library
 *
 * @section intro_sec Introduction
 *
 * This is a library for debouncing buttons with support for polarity adjustment.
 *
 * @section author Author
 * Written by Limor Fried (Ladyada) for Adafruit Industries and ChatGPT-4.
 *
 * @section license License
 * MIT license, all text above must be included in any redistribution.
 */

#ifndef ADAFRUIT_DEBOUNCE_H
#define ADAFRUIT_DEBOUNCE_H

#include "Arduino.h"

class Adafruit_Debounce {
  public:
    Adafruit_Debounce(int16_t pin, bool polarity = LOW);
    void begin();
    void begin(bool initialState);
    bool read();
    void update();
    void update(bool bit);
    bool isPressed();
    bool isReleased();
    bool justPressed();
    bool justReleased();

  private:
    int16_t _pin;
    bool _polarity;
    bool _buttonState; 
    bool _lastButtonState; 
};

#endif // ADAFRUIT_DEBOUNCE_H
