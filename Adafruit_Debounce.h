/*!
 * @file Adafruit_Debounce.h
 */

#ifndef ADAFRUIT_DEBOUNCE_H
#define ADAFRUIT_DEBOUNCE_H

#include "Arduino.h"

/**! Simple debounce state class **/

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
