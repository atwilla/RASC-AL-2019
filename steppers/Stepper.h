class Stepper {
  public:
    Stepper(int enablePin, int pulsePin, int dirPin);
    void step(int dir);
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

void Stepper::step(int dir) {

    int pulseDelay = 100; // This equals 0.5 * Period.
    digitalWrite(dirPin, HIGH); //Spins CW w/ respect to back by default.
    if (dir == 0) {
        digitalWrite(dirPin, LOW);
    }

    // Driver suggests delay between setting direction and driving.
    delayMicroseconds(10);

    digitalWrite(pulsePin, HIGH);
    //Serial.print("Stepping\n");
    delayMicroseconds(pulseDelay);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(pulseDelay);
}
