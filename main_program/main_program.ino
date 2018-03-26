bool init = false;

void setup() {
  Serial.begin(960);
}

void loop() {
  if (!init) {
    Serial.print("Hello!");
    init = true;
  }
  delay(500);
}
