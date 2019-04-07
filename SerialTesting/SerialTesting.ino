void setup() {
  Serial.begin(2000000);
  Serial.println("Ready");
  pinMode(39, OUTPUT);
}

void loop() {
  char letter = ' ';
  char code;

  /*if (Serial.available()) {
    letter = Serial.read();
    Serial.println(letter);
  }*/

  if (Serial.available()) {
    code = Serial.read();

    if (code == 100) {
      digitalWrite(39, HIGH);
    } else {
      digitalWrite(39, LOW);
    }
  }
}
