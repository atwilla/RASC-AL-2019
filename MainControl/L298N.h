/*
 * L298N Motor Driver Board library. Fit for DC motors. 
 * Stepper motor functionality not yet added.
 *  
 * Patrick Buchanan - 5/11/2019
 */

#ifndef L298N_h
#define L298N_h

#include "Arduino.h"

class L298N
{
  public:
    //Functions
    L298N(int A1, int A2, int Aspeed, int B1, int B2, int Bspeed);
    void DC_Drive(char dir, char motor, int _speed);
    void DC_Stop(char motor);

    //Pins
    int dir1PinA;
    int dir2PinA;
    int speedPinA;
    int dir1PinB;
    int dir2PinB;
    int speedPinB;
};

#endif
