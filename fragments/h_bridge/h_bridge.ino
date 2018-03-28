
// Enumerable Motors
const byte M1 = 1;
const byte M2 = 2;
const byte FWD = 0;
const byte BWD = 1; 

// Motor1 Pins
const byte HB1CTRL1 = 2;
const byte HB1CTRL2 = 4;
const byte HB1ENA = 3; // PWM

// Motor2 Pins
const byte HB2CTRL1 = 7;
const byte HB2CTRL2 = 8;
const byte HB2ENA = 5; // PWM

// Motor1 global variables
int m1_ena = 0;
int m1_dir = FWD;
int m1_spd = 0;


// Motor2 global variables
int m2_ena = 0;
int m2_dir = FWD;
int m2_spd = 0;

void setup() {
  pinMode(HB1CTRL1, OUTPUT);
  pinMode(HB1CTRL2, OUTPUT);
  pinMode(HB1ENA, OUTPUT);
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
    analogWrite(HB1ENA, m1_spd);
  } else if (motor == M2) {
    analogWrite(HB2ENA, m2_spd);
  }
}

void disableM(byte motor) {
  if (motor == M1) {
    digitalWrite(HB1ENA, 0);
  } else if (motor == M2) {
    digitalWrite(HB2ENA, 0);
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
    digitalWrite(HB1CTRL1, HIGH);
    digitalWrite(HB1CTRL2, LOW);
    m1_dir = BWD;
  } else if (m1_dir == BWD) {
    digitalWrite(HB1CTRL1, LOW);
    digitalWrite(HB1CTRL2, HIGH);
    m1_dir = FWD;
  }
}

void reverseM2() {
  if (m2_dir == FWD) {
    digitalWrite(HB2CTRL1, HIGH);
    digitalWrite(HB2CTRL2, LOW);
    m1_dir = FWD;
  } else if (m1_dir == BWD) {
    digitalWrite(HB2CTRL1, LOW);
    digitalWrite(HB2CTRL2, HIGH);
    m2_dir = BWD;
  }
}

