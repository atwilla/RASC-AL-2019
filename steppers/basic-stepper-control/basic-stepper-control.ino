// defines pins numbers
const int stepPin = 5; 
const int dirPin = 2; //LOW = CW, HIGH = CCW w/ respect to back of motor.
const int enPin = 8;
const int rightPin = 12;
const int leftPin = 13;

void setup() {
  
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(enPin,OUTPUT);
  
  digitalWrite(enPin,LOW); // 
  
}
void loop() {
  
  digitalWrite(stepPin, LOW);

  while (digitalRead(rightPin) == HIGH) {
    //Rotate motor clockwise while rightPin pressed.
    
    driveMotor(1);
  }

  while (digitalRead(leftPin) == HIGH) {
    //Rotate motor counterclockwise while leftPin pressed.

    driveMotor(0);
  }
}

void driveMotor(short direction) {
  // Rotate the motor in the given direction (1 for cw; 0 for ccw).
  // Directions are with respect to the back of the motor.
 
  const int pulseDelay = 100;

  digitalWrite(dirPin, HIGH);
  if (!direction) digitalWrite(dirPin, LOW);

  // Driver suggest at least 5 us between dir and pulse.
  delayMicroseconds(10);
  
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(pulseDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(pulseDelay);
}
