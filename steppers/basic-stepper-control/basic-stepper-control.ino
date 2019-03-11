#include "Stepper.h"

// define pins numbers
const int rightPin = 12;
const int leftPin = 10;
const int enablePin = 8;
const int pulsePin = 2;
const int dirPin = 5;

int serialCtrl = 0;

Stepper stepper1(enablePin, pulsePin, dirPin);

void setup() {
  Serial.begin(2000000);
  // Enable control pins.
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
}

void loop() {

  if (Serial.available() > 0) {
    serialCtrl = Serial.parseInt();
  }

  int startTime = millis();
  
  if (serialCtrl == 1) {
    while (millis() - startTime < 1000) {
      stepper1.stepCW();
    }
  }
  
  if (serialCtrl == 2) {
    while (millis() - startTime < 1000) {
      stepper1.stepCCW();
    }
  }
  
  while (digitalRead(rightPin) == HIGH) {
    //Rotate motor clockwise while rightPin pressed.

    stepper1.stepCW();
    //Serial.print("right pressed\n");
    //digitalWrite(8, HIGH);
    
  }

  while (digitalRead(leftPin) == HIGH) {
    //Rotate motor counterclockwise while leftPin pressed.

    stepper1.stepCCW();
    //Serial.print("left pressed\n");
  }

  digitalWrite(dirPin, LOW);
}
