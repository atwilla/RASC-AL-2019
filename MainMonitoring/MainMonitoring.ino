const int currentSensor = A0;
const int ff1 = A1, ff2 = A2, ff3 = A3, ff4 = A4;
const float mVPerAmp = 125.0;

float getIRMS(int sensorPin) {
  float maxRead = 0, minRead = 1024, currRead;
  int start, limit = 170;

  start = millis();

  // Take measurement over 1 period of the current.
  /*while (millis() - start <= limit) {
    currRead = analogRead(sensorPin);
    
    // Current sensor outputs voltage such that 512 = 0 Amps. 
    // Below = negative, above = positive.
    if (currRead > maxRead) {
      maxRead = currRead;
    }

    if (currRead < minRead) {
      minRead = currRead;
    }
  }*/

  for (int i = 0; i < 1000; i++) {
    currRead = analogRead(sensorPin);
    if (currRead > maxRead) {
      maxRead = currRead;
    }
  }

  // Convert analog read to a voltage in mV. Convert that to Amps.
  float IRMS = ((maxRead - 512) / 1023) * 5000 * 0.707 * 0.00165;

  /*if (abs(minRead - 512) > abs(maxRead - 512) || maxRead == 0) {
    //IRMS = abs(((minRead / 1023.0) * 5000 - 2500) / mVPerAmp);
    IRMS = 0.0353 * minRead - 18.2;
    
  } else {
    //IRMS = ((maxRead / 1023.0) * 5000 - 2500) / mVPerAmp;
    IRMS = 0.0353 * maxRead - 18.2;
  }*/
  
  return IRMS;
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
  float amps = getIRMS(currentSensor), weightOnBit = getWoB();
  delay(1000);
  Serial.println('C');
  /*Serial.print(amps);
  Serial.print('W');
  Serial.print(weightOnBit);*/

  Serial.println(amps);
}
