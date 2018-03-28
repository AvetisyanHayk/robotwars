const byte IR_R = A0;
const byte IR_T = 12;

void setup() {
  pinMode(IR_R, INPUT);
  pinMode(IR_T, OUTPUT);
  Serial.begin(9600);
  /* Intel */
  attachInterrupt(IR_R, readSensor, FALLING);
  

  /* Arduino 
  attachInterrupt(digitalPinToInterrupt(IR_R), readSensor, FALLING);
  */
}

void loop() {
  analogRead(IR_R);
  digitalWrite(IR_T, HIGH);
  delay(5);
  digitalWrite(IR_T, LOW);
  delay(1000);
}

void readSensor() {
  Serial.write("We have been hit!");
}
