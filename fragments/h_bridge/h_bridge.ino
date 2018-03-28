
// Motor1 Pins
const byte M1_FWD = 2;
const byte M1_REV = 4;
const byte M1_ENA = 3; // PWM

// Motor2 Pins
const byte M2_FWD = 7;
const byte M2_REV = 8;
const byte M2_ENA = 9; // PWM

// Enumerable Motors
const byte M1 = 1;
const byte M2 = 2;
const byte FWD = 0;
const byte BWD = 1;

// Motor1 global variables
int m1_ena = 0;
int m1_dir = FWD;
int m1_spd = 0;

// Motor2 global variables
int m2_ena = 0;
int m2_dir = FWD;
int m2_spd = 0;

void setup() {
  pinMode(M1_FWD, OUTPUT);
  pinMode(M1_REV, OUTPUT);
  pinMode(M1_ENA, OUTPUT);
  pinMode(M2_FWD, OUTPUT);
  pinMode(M2_REV, OUTPUT);
  pinMode(M2_ENA, OUTPUT);
  disableMotors();
}

void loop() {
 testMotor();
}

void testMotor() {
  m1_spd = 100;
  enableM(M1);
  delay(1000);
  disableM(M1);
  delay(1000);
  reverseM(M1);
  enableM(M1);
  delay(1000);
  disableM(M1);
  delay(1000);
  reverseM(M1);
}

void enableM(byte motor) {
  if (motor == M1) {
    analogWrite(M1_ENA, m1_spd);
  } else if (motor == M2) {
    analogWrite(M2_ENA, m2_spd);
  }
}

void disableM(byte motor) {
  if (motor == M1) {
    digitalWrite(M1_ENA, 0);
  } else if (motor == M2) {
    digitalWrite(M2_ENA, 0);
  }
}

void disableMotors() {
  disableM(M1);
  disableM(M2);
}

void reverseM(byte motor) {
  if (motor == M1) {
    reverseM1();
  } else if (motor == M2) {
    reverseM2();
  }
}

void reverseM1() {
  if (m1_dir == FWD) {
    digitalWrite(M1_FWD, HIGH);
    digitalWrite(M1_REV, LOW);
    m1_dir = BWD;
  } else if (m1_dir == BWD) {
    digitalWrite(M1_FWD, LOW);
    digitalWrite(M1_REV, HIGH);
    m1_dir = FWD;
  }
}

void reverseM2() {
  if (m2_dir == FWD) {
    digitalWrite(M2_FWD, HIGH);
    digitalWrite(M2_REV, LOW);
    m1_dir = FWD;
  } else if (m1_dir == BWD) {
    digitalWrite(M2_FWD, LOW);
    digitalWrite(M2_REV, HIGH);
    m2_dir = BWD;
  }
}

