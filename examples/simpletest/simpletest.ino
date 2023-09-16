#include "Adafruit_Debounce.h"

// Define the button pin use any GPIO
#define BUTTON_PIN 4

// Create a debounce object for the button, which will be pressed when LOW
Adafruit_Debounce button(BUTTON_PIN, LOW);

void setup() {
  // Start the serial communication
  Serial.begin(115200);

  // Initialize the button, which will set the pull-up as well!
  button.begin();
}

void loop() {
  // Update the button state, this will do the digitalRead() for us
  // must be called ~every 10ms to keep state and catch presses 
  button.update();

  if (button.justPressed()) {
    Serial.println("Button was just pressed!");
  }

  if (button.justReleased()) {
    Serial.println("Button was just released!");
  }

  // Add a small debouncing delay
  delay(10);
}
