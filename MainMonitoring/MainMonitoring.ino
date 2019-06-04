const int currentSensor = A4, pulsePin = 13;
const int ff1 = A0, ff2 = A1, ff3 = A2, ff4 = A3;
const float mVPerAmp = 125.0;
const float microstep = 1/ 32, cmPerRot = 0.254, stepAngle = 1.8;
float baseWeight;
int steps = 0, prevState;
int startTime;

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
  return baseWeight - getWeight();
}

void setup() {
  Serial.begin(2000000);
  pinMode(currentSensor, INPUT);
  pinMode(ff1, INPUT);
  pinMode(ff2, INPUT);
  pinMode(ff3, INPUT);
  pinMode(ff4, INPUT);
  pinMode(pulsePin, INPUT);
  prevState = digitalRead(pulsePin);

  baseWeight = getWeight();
  startTime = millis();
}

void loop() {
  int currState = digitalRead(pulsePin);
  if (prevState != currState) {
    steps++;
    prevState = currState;
  }
  
  float amps = getIRMS(currentSensor), weightOnBit = getWoB();
  float depth = steps *cmPerRot * stepAngle * microstep / 360;

  if (millis() - startTime > 500) {
    Serial.println('C');
    Serial.println(amps);
    Serial.println('W');
    Serial.println(weightOnBit);
    Serial.println('D');
    Serial.println(depth);
    startTime = millis();
  }
}
