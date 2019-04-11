#include "Stepper.h"

char controlCode, lastDigit;

bool locked = false;
bool transStepEn = true, transStep = false, transStepDir = true;
bool vertStepEn = true, vertStep = false, vertStepDir = true;
bool heating = false;
bool pump = false, pumpDir = true;
bool largeLin = false, largeLineDir = true;
bool smallLin = false, smallLinDir = true;

//Enable, direction, pulse.
Stepper transMotors(48, 50, 52);

void setup() {
  Serial.begin(2000000);
  
  pinMode(48, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(52, OUTPUT);

  //digitalWrite(48, HIGH);
  //digitalWrite(50, HIGH);
  //digitalWrite(52, HIGH);
}

void loop() {
  // If a code is available, read it in, and flip the appropriate variables.
  if (Serial.available()) {
    controlCode = Serial.read();
    lastDigit = controlCode % 10;
    Serial.println(controlCode);
    
    if (controlCode >= 60) {
      // Vertical stepper options.

      switch (lastDigit) {
        case 0:
          vertStepEn = false;
          break;
        case 1:
          vertStepEn = true;
          break;
        case 2:
          vertStep = true;
          vertStepDir = true;
          break;
        case 3:
          vertStep = true;
          vertStepDir = false;
          break;
        case 4:
          vertStep = false;
          break;
        default:
          break;
      }
      
    } else if (controlCode >= 50) {
      // Small actuator options.
      
    } else if (controlCode >= 40) {
      // Transverse actuator options.
      
    } else if (controlCode >= 30) {
      // Pump options.
      
    } else if (controlCode >= 20) {
      // Heating element options.
      
    } else if (controlCode >= 10) {
      // Transverse steppers options.

      switch (lastDigit) {
        case 0:
          transStepEn = false;
          transMotors.disable();
          break;
        case 1:
          transStepEn = true;
          transMotors.enable();
          break;
        case 2:
          transStep = true;
          transStepDir = true;
          break;
        case 3:
          transStep = true;
          transStepDir = false;
          break;
        case 4:
          transStep = false;
          break;
        default:
          break;
      }
      
    } else if (controlCode >= 0) {
      // Safety options.
      
    }
  }

  // Check all control vars and act accordingly.

  // Transverse stepper actions
  if (transStepEn) {
  
    if (transStep) {
      
      if (transStepDir) {
        transMotors.stepCW();
        
      } else {
        transMotors.stepCCW();
      }
    }
  }
}
