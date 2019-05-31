const int currentSensor = A4;
const int ff1 = A0, ff2 = A1, ff3 = A2, ff4 = A3;
const float mVPerAmp = 125.0;
float baseWeight;

float getIRMS(int sensorPin) {
  float maxRead = 0, currRead;

  for (int i = 0; i < 1000; i++) {
    currRead = analogRead(sensorPin);
    if (currRead > maxRead) {
      maxRead = currRead;
    }
  }

  // Convert analog read to a voltage in mV. Convert that to Amps.
  return ((maxRead - 512) / 1023) * 5000 * 0.707 * 0.00165;
}

float getWeight() {
  float sensorSum = 0;

  sensorSum += analogRead(ff1);
  sensorSum += analogRead(ff2);
  sensorSum += analogRead(ff3);
  sensorSum += analogRead(ff4);

  return sensorSum * -0.1179 + 475.957;
}

float getWoB() {
  return getWeight() - baseWeight;
}

void setup() {
  Serial.begin(2000000);
  pinMode(currentSensor, INPUT);
  pinMode(ff1, INPUT);
  pinMode(ff2, INPUT);
  pinMode(ff3, INPUT);
  pinMode(ff4, INPUT);

  baseWeight = getWeight();
}

void loop() {
  float amps = getIRMS(currentSensor), weightOnBit = getWoB();
  delay(250);
  Serial.println('C');
  Serial.println(amps);
  Serial.println('W');
  Serial.println(weightOnBit);
}
