const int sensors[4] = {A0, A1, A2, A3};
char start;

void setup() {
  Serial.begin(2000000);

  for (int i = 0; i < 4; i++) {
    pinMode(sensors[i], INPUT);
  }
}

void loop() {
  float grandSum = 0;
  start = 'a';
  
  if (Serial.available()) {
    start = Serial.read();
  }

  if (start == 's') {
    for (int sensor = 0; sensor < 4; sensor++) {
  
      float sum = 0, avg;
  
      for (int i = 0; i < 100; i++) {
        sum += analogRead(sensors[sensor]);
      }
  
      avg = sum / 100;
      grandSum += avg;
  
      Serial.print("Sensor ");
      Serial.print(sensor);
      Serial.print(": ");
      Serial.println(avg);
    }
  
    Serial.print("Sum: ");
    Serial.println(grandSum);
  }
}
