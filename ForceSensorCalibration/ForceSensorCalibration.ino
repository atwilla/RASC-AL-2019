const int sensorPin = A0;
char start;

void setup() {
  Serial.begin(2000000);
  pinMode(sensorPin, INPUT);
}

void loop() {
  float sum = 0, avg;
  start = 'a';
  
  if (Serial.available()) {
    start = Serial.read();
  }

  if (start == 's') {

    for (int i = 0; i < 1000; i++) {
      sum += analogRead(sensorPin);
    }

    avg = sum / 1000;

    Serial.print("Average Value Read: ");
    Serial.println(avg);
  }
}
