#include "StepperMotor.h"

/*class Stepper {
  public:
    Stepper(int enablePin, int pulsePin, int dirPin);
    void stepCW();
    void stepCCW();
    void disable();
    void enable();

  private:
    int enablePin;
    int pulsePin;
    int dirPin;
};

Stepper::Stepper(int enablePin, int pulsePin, int dirPin) {
    // Constructor for Stepper class. Given pins will be enabled 
    // as output pins.
   
    this->enablePin = enablePin;
    this->pulsePin = pulsePin;
    this->dirPin = dirPin;
    
    // Reduce code required to use stepper.
    pinMode(enablePin, OUTPUT);
    pinMode(pulsePin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    // Enable pin disables driver on HIGH.
    digitalWrite(enablePin, LOW);
    digitalWrite(pulsePin, LOW);
}

void Stepper::stepCW() {

    int pulseDelay = 100; // This equals 0.5 * Period.
    digitalWrite(dirPin, HIGH); //Spins CW w/ respect to back by default.

    // Driver suggests delay between setting direction and driving.
    delayMicroseconds(10);

    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(pulseDelay);
}

void Stepper::stepCCW() {

    int pulseDelay = 100;
    digitalWrite(dirPin, LOW);

    delayMicroseconds(10);

    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(pulseDelay);
}*/

// define pins numbers
const int rightPin = 12;
const int leftPin = 10;
const int enablePin = 8;
const int pulsePin = 2;
const int dirPin = 5;

Stepper stepper1(enablePin, pulsePin, dirPin);

void setup() {

  // Enable control pins.
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
}

void loop() {
  
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
