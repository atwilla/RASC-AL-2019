class Stepper {
  public:
    Stepper(int enablePin, int dirPin, int pulsePin);
    void stepCW(int pulseDelay = 100);
    void stepCCW(int pulseDelay = 100);
    void disable();
    void enable();

  private:
    int enablePin;
    int pulsePin;
    int dirPin;
    int pulseDelay;
};

Stepper::Stepper(int enablePin, int dirPin, int pulsePin) {
    // Constructor for Stepper class. Given pins will be enabled 
    // as output pins.
   
    this->enablePin = enablePin;
    this->pulsePin = pulsePin;
    this->dirPin = dirPin;
    //this->pulseDelay = 100;
    
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
    delayMicroseconds(pulseDelay);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(pulseDelay);
}

void Stepper::stepCCW(int pulseDelay) {

    //int pulseDelay = 100;
    digitalWrite(dirPin, LOW);

    delayMicroseconds(10);

    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(pulseDelay);
}

void Stepper::enable() {
	digitalWrite(enablePin, LOW);
}

void Stepper::disable() {
	digitalWrite(enablePin, HIGH);
  digitalWrite(dirPin, LOW);
  digitalWrite(pulsePin, LOW);
}
