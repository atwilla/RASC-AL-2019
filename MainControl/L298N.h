/*
 * L298N Motor Driver Board library. Fit for DC motors. 
 * Stepper motor functionality not yet added.
 *  
 * Patrick Buchanan - 5/11/2019
 */

#ifndef L298N_h
#define L298N_h

//#include "Arduino.h"

class L298N {
    private:
        int dir1PinA;
        int dir2PinA;
        int speedPinA;
        int dir1PinB;
        int dir2PinB;
        int speedPinB;

    public:
        L298N(int A1, int A2, int Aspeed, int B1, int B2, int Bspeed){
            dir1PinA = A1;
            dir2PinA = A2;
            speedPinA = Aspeed;
            dir1PinB = B1;
            dir2PinB = B2;
            speedPinB = Bspeed;

            pinMode(dir1PinA, OUTPUT);
            pinMode(dir2PinA, OUTPUT);
            pinMode(speedPinA, OUTPUT);
            pinMode(dir1PinB, OUTPUT);
            pinMode(dir2PinB, OUTPUT);
            pinMode(speedPinB, OUTPUT);

        }

        void drive(char dir, char motor, int _speed){
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

                //Set speed
                analogWrite(speedPinB, _speed);

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
            }
        }

        void stop(char motor){
            //Motor A selected
            if(motor == 'A' || motor == 'a'){
                analogWrite(speedPinA, 0);
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, LOW);
            }

            //Motor B selected
            if(motor == 'B' || motor == 'b'){
                analogWrite(speedPinB, 0);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, LOW);
            }
        }
};

#endif
