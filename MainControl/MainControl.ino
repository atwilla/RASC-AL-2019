#include "Relay.h"
#include "Pump.h"
#include "Stepper.h"

char controlCode, lastDigit;

bool locked = false;
bool transStepEn = true, transStep = false, transStepDir = true;
bool vertStepEn = true, vertStep = false, vertStepDir = true;
bool heatingMode = false;
bool heatingEn = false;
bool pumpEn = false, pumpDir = true;
bool largeLinEn = false, largeLinDir = true;
bool smallLinEn = false, smallLinDir = true;

const int heatingPin = 52;
const int transEnPin = 22, transDirPin = 24, transPulPin = 26;
const int vertEnPin = 23, vertDirPin = 25, vertPulPin = 27;

Relay HeatingElement(heatingPin);

//Enable, direction, pulse.
Stepper transMotors(transEnPin, transDirPin, transPulPin);
Stepper vertMotor(vertEnPin, vertDirPin, vertPulPin);

void setup() {
  Serial.begin(2000000);
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

      if (lastDigit == 0) {
        smallLinEn = false;
       
      } else if (lastDigit == 1) {
        //Extend actuator.
        smallLinEn = true;
        smallLinDir = true;
        
      } else if (lastDigit == 2) {
        // Retract actuator.
        smallLinEn = true;
        smallLinDir = false;
      }
      
    } else if (controlCode >= 40) {
      // Large actuator options
      
      if (lastDigit == 0) {
        largeLinEn = false;
        
      } else if (lastDigit == 1) {
        // Extend actuator.
        largeLinEn = true;
        largeLinDir = true;
        
      } else if (lastDigit == 2) {
        // Retract actuator
        largeLinEn = true;
        largeLinDir = false;
      }
      
    } else if (controlCode >= 30) {
      // Pump options.

      if (lastDigit == 0) {
        // Stop pump.
        pumpEn = false;
        
      } else if (lastDigit == 1) {
        // Pump forward.
        pumpEn = true;
        pumpDir = true;
        
      } else if (lastDigit == 2) {
        // Pump backward.
        pumpEn = true;
        pumpDir = false;
      }
      
    } else if (controlCode >= 20) {
      // Heating element options.

      if (lastDigit == 0) {
        heatingEn = true;
      } else {
        heatingEn = false;
      }
      
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

  //Vertical stepper actions
  if (vertStepEn) {

    if (vertStep) {

      if (vertStepDir) {
        vertMotor.stepCW(500); 
             
      } else {
        vertMotor.stepCCW(500);
      }
    }
  }

  // Small actuator actions.
  if (smallLinEn) {

    if (smallLinDir) {
      // Extend.
    } else {
      // Retract.
    }
  }

  // Large actuator actions.
  if (largeLinEn) {

    if (largeLinDir) {
      // Extend.
    } else {
      // Retract.
    }
  }

  // Pump actions.
  if (pumpEn) {
    
    if (pumpDir) {
      // Pump forwards.
    } else {
      // Pump backwards.
    }
  }

  // Heating actions
  if (heatingEn) {
    // Actiate heating element.
  }
  
  // Transverse stepper actions
  if (transStepEn) {
  
    if (transStep) {
      
      if (transStepDir) {
        transMotors.stepCW(500);
        
      } else {
        transMotors.stepCCW(500);
      }
    }
  }

}
