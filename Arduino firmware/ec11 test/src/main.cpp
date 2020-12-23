#include <Arduino.h>

#include "EC11.hpp"

//
// Here we assume that the pins A and B of a EC-11 rotary encoder are connected to pins 2 and 3 of the Arduino Uno
// board and the pin C is connected to the ground.
//

EC11 encoder;

//
// Interrupt-based example. This is recommended, but it means only pins 2 and 3 can be used with Uno.
//
bool led;
const int encoderPinA = 2;
const int encoderPinB = 3;

void pinDidChange() {
  encoder.checkPins(digitalRead(encoderPinA), digitalRead(encoderPinB));
}

void prepare() {
  attachInterrupt(0, pinDidChange, CHANGE);
  attachInterrupt(1, pinDidChange, CHANGE);
}


void setup() {

  // We can use internal pull-up with the encoder pins, assuming pin C is simply grounded.
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  led = 0;
  prepare();
    EC11Event e;
}

static int value = 0;

void loop() {

  EC11Event e;
  if (encoder.read(&e)) {

    // OK, got an event waiting to be handled
    led = !led;
    digitalWrite(4, led);
  }
}
