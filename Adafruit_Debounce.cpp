/*!
 * @file Adafruit_Debounce.cpp
 *
 * @mainpage Adafruit Button Debounce library
 *
 * @section intro_sec Introduction
 *
 * This is a library for debouncing buttons with support for polarity
 * adjustment.
 *
 * @section author Author
 * Written by Limor Fried (Ladyada) for Adafruit Industries and ChatGPT-4.
 *
 * @section license License
 * MIT license, all text above must be included in any redistribution.
 */

#include "Adafruit_Debounce.h"

/**
 * @brief Construct a new Adafruit_Debounce::Adafruit_Debounce object.
 *
 * @param pin The pin number associated with the button. If pin is < 0 we can
 * use an expander instead of the built in GPIO support.
 * @param polarity The polarity to determine the pressed state (default is LOW
 * which means the input is LOW when the button is pressed).
 */
Adafruit_Debounce::Adafruit_Debounce(int16_t pin, bool polarity) {
  _pin = pin;
  _polarity = polarity;
  _buttonState = !_polarity;
  _lastButtonState = !_polarity;
}

/**
 * @brief Initialize the debounce object.
 *
 * This function sets the pin mode based on the polarity and initializes
 * the button states. This assumes that the pin is GPIO (>= 0), otherwise please
 * use the other begin(bool) which allows you to initialize the button start
 * state.
 */
void Adafruit_Debounce::begin() {
  if (_pin >= 0) {
    if (_polarity == LOW) {
      pinMode(_pin, INPUT_PULLUP);
    } else {
#ifdef INPUT_PULLDOWN
      pinMode(_pin, INPUT_PULLDOWN);
#else
      pinMode(_pin, INPUT);
#endif
    }

    _buttonState = digitalRead(_pin);
    _lastButtonState = _buttonState;
  }
}

/**
 * @brief Initialize the debounce object with a given initial state. Good for
 * use with expanders.
 *
 * @param initialState The initial state to set the button states.
 */
void Adafruit_Debounce::begin(bool initialState) {
  begin();
  _buttonState = initialState;
  _lastButtonState = initialState;
}

/**
 * @brief Read the current state of the button. Will call digitalRead if the pin
 * is >= 0, otherwise returns the internal state.
 *
 * @return Pin current digital state (not adjusted for polarity!)
 */
bool Adafruit_Debounce::read() {
  if (_pin >= 0) {
    return digitalRead(_pin);
  }
  return _buttonState;
}

/**
 * @brief Update the button states based on the current pin reading.
 *
 * This function updates the button states based on the result of digitalRead().
 * Not for use with a GPIO expander
 */
void Adafruit_Debounce::update() {
  if (_pin >= 0) {
    _lastButtonState = _buttonState;
    _buttonState = digitalRead(_pin);
  }
}

/**
 * @brief Update the button states with a given state. Good for use with
 * expanders.
 *
 * @param bit The digital state to set the button. Not adjusted for polarity!
 */
void Adafruit_Debounce::update(bool bit) {
  _lastButtonState = _buttonState;
  _buttonState = bit;
}

/**
 * @brief Check if the button is currently pressed, adjusted for polarity
 *
 * @return true If the button is pressed.
 * @return false Otherwise.
 */
bool Adafruit_Debounce::isPressed() { return _buttonState == _polarity; }

/**
 * @brief Check if the button is currently released, adjusted for polarity
 *
 * @return true If the button is released.
 * @return false Otherwise.
 */
bool Adafruit_Debounce::isReleased() { return _buttonState != _polarity; }

/**
 * @brief Check if the button was just pressed since last update(), adjusted for
 * polarity
 *
 * @return true If the button was just pressed since last update()
 * @return false Otherwise.
 */
bool Adafruit_Debounce::justPressed() {
  return (_buttonState != _lastButtonState) && (_buttonState == _polarity);
}

/**
 * @brief Check if the button was just released since last update(), adjusted
 * for polarity
 *
 * @return true If the button was just released since last update()
 * @return false Otherwise.
 */
bool Adafruit_Debounce::justReleased() {
  return (_buttonState != _lastButtonState) && (_buttonState != _polarity);
}
