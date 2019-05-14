#include "Arduino.h"
#include "L298N.h"

//Constructor
L298N::L298N(int A1, int A2, int Aspeed, int B1, int B2, int Bspeed){
  //Set pin modes.
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(Aspeed, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(Bspeed, OUTPUT);

  //Set variables to those pins.
  dir1PinA = A1;
  dir2PinA = A2;
  speedPinA = Aspeed;
  dir1PinB = B1;
  dir2PinB = B2;
  speedPinB = Bspeed;
}

//Drive function for DC motors.
void L298N::DC_Drive(char dir, char motor, int _speed){
  //Motor A selected.
  if(motor == 'A' || motor == 'a'){
    
    //Forward
    if(dir == 'F' || dir == 'f'){
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
    }

    //Reverse
    if(dir == 'R' || dir == 'r'){
      digitalWrite(dir1PinA, HIGH);
      digitalWrite(dir2PinA, LOW);
    }

    //Set speed
    analogWrite(speedPinA, _speed);
  }

  //Motor B selected.
  if(motor == 'B' || motor == 'b'){
    
    //Forward
    if(dir == 'F' || dir == 'f'){
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, HIGH);
    }

    //Reverse
    if(dir == 'R' || dir == 'r'){
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
    }

    //Set speed
    analogWrite(speedPinB, _speed);
  }
}

//Stop selected motor
void L298N::DC_Stop(char motor){
  //Motor A selected
  if(motor == 'A' || motor == 'a'){
    analogWrite(speedPinA, 0);
  }

  //Motor B selected
  if(motor == 'B' || motor == 'b'){
    analogWrite(speedPinB, 0);
  }
}
