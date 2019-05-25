const int currentSensor = A0;
const int ff1 = A1, ff2 = A2, ff3 = A3, ff4 = A4;
const float mVPerAmp = 100.0;

float getIMax(int sensorPin) {
  float maxRead = 0, minRead = 1024, currRead;
  int start, limit = 17;

  start = millis();

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

float getWoB() {
  return 0.0;
}

void setup() {
  Serial.begin(2000000);
  pinMode(currentSensor, INPUT);
  pinMode(ff1, INPUT);
  pinMode(ff2, INPUT);
  pinMode(ff3, INPUT);
  pinMode(ff4, INPUT);
}

void loop() {
  float amps = getIMax(currentSensor), weightOnBit = getWoB();
  delay(1000);
  Serial.print('C');
  Serial.print(amps);
  Serial.print('W');
  Serial.print(weightOnBit);
}
