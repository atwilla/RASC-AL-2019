class Stepper {
  public:
    Stepper(int enablePin, int dirPin, int pulsePin, float stepAngle, float microstep, float distPerTurn);
    void stepCW(int pulseDelay = 100);
    void stepCCW(int pulseDelay = 100);
    void disable();
    void enable();
    void updateDistance(bool dir);
    void resetDistance();
    int distanceTravelled;

  private:
    int enablePin;
    int pulsePin;
    int dirPin;
    float stepAngle;
    float microstep;
    float distPerTurn;
};

Stepper::Stepper(int enablePin, int dirPin, int pulsePin, float stepAngle, float microstep, float distPerTurn) {
    // Constructor for Stepper class. Given pins will be enabled 
    // as output pins.
   
    this->enablePin = enablePin;
    this->pulsePin = pulsePin;
    this->dirPin = dirPin;
    this->distanceTravelled = 0;
    this->stepAngle = stepAngle;
    this->microstep = microstep;
    this->distPerTurn = distPerTurn;
    
    // Reduce code required to use stepper.
    pinMode(enablePin, OUTPUT);
    pinMode(pulsePin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    // Enable pin disables driver on HIGH.
    digitalWrite(enablePin, LOW);
    digitalWrite(pulsePin, LOW);
}

void Stepper::stepCW(int pulseDelay) {

    //int pulseDelay = 100; // This equals 0.5 * Period.
    digitalWrite(dirPin, HIGH); //Spins CW w/ respect to back by default.

    // Driver suggests delay between setting direction and driving.
    delayMicroseconds(10);

    digitalWrite(pulsePin, HIGH);
    //delayMicroseconds(pulseDelay);
    digitalWrite(pulsePin, LOW);
    updateDistance(false);
    //delayMicroseconds(pulseDelay);
}

void Stepper::stepCCW(int pulseDelay) {

    //int pulseDelay = 100;
    digitalWrite(dirPin, LOW);

    delayMicroseconds(10);

    digitalWrite(pulsePin, HIGH);
    //delayMicroseconds(pulseDelay);
    digitalWrite(pulsePin, LOW);
    updateDistance(true);
    //delayMicroseconds(pulseDelay);
}

void Stepper::enable() {
	digitalWrite(enablePin, LOW);
}

void Stepper::disable() {
	digitalWrite(enablePin, HIGH);
  digitalWrite(dirPin, LOW);
  digitalWrite(pulsePin, LOW);
}

void Stepper::updateDistance(bool dir) {
  if (dir) {
    distanceTravelled += distPerTurn * stepAngle * microstep * 2;
  } else {
    distanceTravelled -= distPerTurn * stepAngle * microstep * 2;
  }
}

void Stepper::resetDistance() {
  distanceTravelled = 0;
}
