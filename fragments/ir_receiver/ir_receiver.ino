const byte IRR = A0;
const byte IRT = 5;

void setup() {
  pinMode(IRR, INPUT);
  pinMode(IRT, OUTPUT);
  Serial.begin(9600);
  /* Intel */
  attachInterrupt(IRR, readSensor, FALLING);
  

  /* Arduino 
  attachInterrupt(digitalPinToInterrupt(IRR), readSensor, FALLING);
  */
}

void loop() {
  analogRead(IRR);
  digitalWrite(IRT, HIGH);
  delay(5);
  digitalWrite(IRT, LOW);
  delay(1000);
}

void readSensor() {
  Serial.write("We have been hit!");
}
