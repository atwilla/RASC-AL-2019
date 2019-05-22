const int currentSensor = A0;
const float mVPerAmp = 100.0;

float getIMax(int sensorPin) {
  float maxRead = 0, minRead = 1024, currRead;
  int start = millis(), limit = (1 / 60) * 1000;

  // Take measurement over 1 period of the current.
  while (millis() - start <= limit) {
    currRead = analogRead(sensorPin);
    
    // Current sensor outputs voltage such that 512 = 0 Amps. 
    // Below = negative, above = positive.
    if (currRead > maxRead) {
      maxRead = currRead;
    }
  }

  // Convert analog read to a voltage in mV. Convert that to Amps.
  float IMax = ((maxRead / 1023.0) * 5000 - 2500) / mVPerAmp;
  return IMax;
}

void setup() {
  Serial.begin(2000000);
  pinMode(currentSensor, INPUT);
}

void loop() {
  float amps = getIMax(currentSensor);
  delay(1000);
  Serial.println(amps);
}
