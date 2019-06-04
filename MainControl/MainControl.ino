#include "HBridge.h"
#include "LinActuator.h"
#include "Relay.h"
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

const int lAct1 = 49, lAct2 = 48, lActPower = 46;
const int sAct1 = 51, sAct2 = 50, sActPower = lActPower;
const int pumpPin = 53;
const int heatingPin = 52;
const int transEnPin = 23, transDirPin = 25, transPulPin = 27;
const int vertEnPin = 22, vertDirPin = 24, vertPulPin = 26;

LinActuator largeActuator(lAct1, lAct2, lActPower);
//LinActuator smallActuator(sAct1, sAct2, sActPower);
int smallActuator = 51;
Relay pump(pumpPin);
Relay heatingElement(heatingPin);

//Enable, direction, pulse.
Stepper transMotors(transEnPin, transDirPin, transPulPin, 1.8, 1 / 64, 0.15);
Stepper vertMotor(vertEnPin, vertDirPin, vertPulPin, 1.8, 1 / 64, 0.254);

void setup() {
  Serial.begin(2000000);
  digitalWrite(lActPower, LOW);
  pinMode(smallActuator, OUTPUT);
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
        case 5:
          vertMotor.resetDistance();
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
        
      } else if (lastDigit == 3) {
        // Pulse actuator forwards.
        smallLinEn = true;
        smallLinDir = true;
        
      } else if (lastDigit == 4) {
        // Pulse actuator backwards.
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
        
      } else if (lastDigit == 3) {
        // Pulse actuator forwards.
        largeLinEn = true;
        largeLinDir = true;
        
      } else if (lastDigit == 4) {
        // Pulse actuator backwards.
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
      digitalWrite(smallActuator, HIGH);
      //smallActuator.drive(1);
    } else {
      // Retract.
      digitalWrite(smallActuator, LOW);
      //smallActuator.drive(0);
    }
    
  }

  // Large actuator actions.
  if (largeLinEn) {

    if (largeLinDir) {
      // Extend.
      largeActuator.drive(1);
    } else {
      // Retract.
      largeActuator.drive(0);
    }
    
  } else {
    largeActuator.stop();
  }

  // Pump actions.
  if (pumpEn) {
    
    if (pumpDir) {
      pump.activate();
    } else {
      //pump.pumpBackwards();
    }
    
  } else {
    pump.deactivate();
  }

  // Heating actions
  if (heatingEn) {
    heatingElement.activate();
  } else {
    heatingElement.deactivate();
  }
}
