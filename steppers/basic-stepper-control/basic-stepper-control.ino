#include "Stepper.h"

// define pins numbers
const int rightPin = 12;
const int leftPin = 10;
const int enablePin = 8;
const int pulsePin = 5;
const int dirPin = 2;

Stepper stepper1(enablePin, pulsePin, dirPin);

void setup() {

  // Enable control pins.
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
  
}
void loop() {
  
  while (digitalRead(rightPin) == HIGH) {
    //Rotate motor clockwise while rightPin pressed.

    stepper1.step(1);
  }

  while (digitalRead(leftPin) == HIGH) {
    //Rotate motor counterclockwise while leftPin pressed.

    stepper1.step(0);
  }
}
