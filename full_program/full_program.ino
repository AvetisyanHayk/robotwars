/*
 * DIGITAL PINS
 */
#define BT1_RX 0          // Bluetooth 1 RX
#define BT1_TX 1          // Bluetooth 1 TX
#define M1_FWD 2          // Motor 1 Forwards
#define M1_ENA 3          // Motor 1 Enable
#define M1_REV 4          // Motor 1 Backwards
#define IR_T 5            // IR Transmitter
#define LED_STRIP 6       // LED Strip
#define M2_FWD 7          // Motor 2 Forwards
#define M2_REV 8          // Motor 2 Backwards
#define M2_ENA 9          // Motor 2 Enable
#define M3_SERVO 10       // Servo angle
#define BUZZER 11         // Piëzo buzzer
#define SDIST_TRIGGER 12  // Distance Sensor Trigger
#define SDIST_ECHO 13     // Distance Sensor Echo

/*
 * ANALOG PINS
 */
#define IR_R A0

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

float distance;

/*
 * SETUP
 */
void setup() {
  setupHBridge();
  setupIR();
  setupDistanceSensors();
  setupDisco();
}

void setupHBridge() {
  pinMode(M1_FWD, OUTPUT);
  pinMode(M1_REV, OUTPUT);
  pinMode(M1_ENA, OUTPUT);
  pinMode(M2_FWD, OUTPUT);
  pinMode(M2_REV, OUTPUT);
  pinMode(M2_ENA, OUTPUT);
  disableMotors();
}

void setupIR() {
  pinMode(IR_R, INPUT);
  pinMode(IR_T, OUTPUT);
  attachInterrupt(IR_R, readSensor, FALLING);
}

void setupDistanceSensors() {
  pinMode(SDIST_ECHO, INPUT); 
  pinMode(SDIST_TRIGGER, OUTPUT); 
  digitalWrite(SDIST_TRIGGER, LOW); 
}

void setupDisco() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_STRIP, OUTPUT);
  pinMode(M3_SERVO, OUTPUT);
}

/*
 * LOOP
 */
void loop() {
  runDistanceSensor();
}

void runDistanceSensor() {
  delay(200); 
  digitalWrite(SDIST_TRIGGER, HIGH); 
  delay(1000);
  digitalWrite(SDIST_TRIGGER, LOW);
  distance = pulseIn(SDIST_ECHO, HIGH) / 58;
  delay(200); 
}

/*
 * MOTOR FUNCTIONALITY
 */

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


/*
 * IR Functionality
 */

 void readSensor() {
  Serial.write("We have been hit!");
}
