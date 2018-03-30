#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

/*
 * COMMANDS
 */
const char GO_FORWARD = 'u';
const char GO_BACKWARD = 'd';
const char GO_LEFT = 'l';
const char GO_RIGHT = 'r';
const char STOP_GOING = 's';
const char FIRE = 'f';
const char HIT = 'h';
const char WARN_DISTANCE = 'w';

/*
 * DIGITAL PINS
 */
#define BT1_RX 0          // Bluetooth 1 RX
#define BT1_TX 1          // Bluetooth 1 TX
#define M1_FWD 2          // Motor 1 Forwards
#define M1_ENA 3          // Motor 1 Enable
#define M1_REV 4          // Motor 1 Backwards
#define IR1_T 5            // IR Transmitter
#define IR2_T 6       // LED Strip
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
const byte REV = 1;

// Motor1 global variables
int m1_ena = 0;
int m1_dir = FWD;
int m1_spd = 0;
const int MAX_SPEED = 255;

// Motor2 global variables
int m2_ena = 0;
int m2_dir = FWD;
int m2_spd = 0;

// Servo global variables
Servo servo;
int servo_angle = 0;

// IR global variables
const int SHOOT_COUNT = 6;
int hitCount = 0;
int currentShot = 0;

// Distance sensor global variables
int distance;
const int SHOOT_DISTANCE = 3;

// Buzzer global variables
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
int buzzerCounter = 0;
const int buzzerTempo = (6000/128) * 4;

// LCD Global Variables
String lcd_line1 = "Pietje Pek !";
String lcd_line2 = "1-BEL-666";
/*
 * SETUP
 */
void setup() {
  setupBluetooth();
  setupHBridge();
  setupIR();
  // setupDistanceSensors();
  // setupDisco();
}

void setupBluetooth() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void setupHBridge() {
  pinMode(M1_FWD, OUTPUT);
  pinMode(M1_REV, OUTPUT);
  pinMode(M1_ENA, OUTPUT);
  pinMode(M2_FWD, OUTPUT);
  pinMode(M2_REV, OUTPUT);
  pinMode(M2_ENA, OUTPUT);
  stopGoing();
}

void setupIR() {
  pinMode(IR_R, INPUT);
  pinMode(IR1_T, OUTPUT);
  pinMode(IR2_T, OUTPUT);
  attachInterrupt(IR_R, readSensor, FALLING);
}

void setupDistanceSensors() {
  pinMode(SDIST_ECHO, INPUT); 
  pinMode(SDIST_TRIGGER, OUTPUT); 
}

void setupDisco() {
  pinMode(BUZZER, OUTPUT);
  servo.attach(M3_SERVO);
}

/*
 * LOOP
 */
void loop() {
  runBluetooth();
  // runDistanceSensor();
  // runDisco();
}

void runBluetooth() {
  if(Serial1.available() > 0){
    char state = Serial1.read();
    Serial.println(state);
    handleState(state);
  }
  if(Serial.available() > 0){
    char inByte = Serial.read();
    Serial1.println(inByte);
  }
}

void runDistanceSensor() {
  digitalWrite(SDIST_TRIGGER, LOW); 
  delay(200); 
  digitalWrite(SDIST_TRIGGER, HIGH); 
  delay(1000); 
  digitalWrite(SDIST_TRIGGER, LOW);
  float distance = pulseIn(SDIST_ECHO, HIGH); 
  distance = distance / 58; 
  Serial.print(distance); 
  Serial.println(" cm");
  if (distance <= SHOOT_DISTANCE) {
    Serial1.write(WARN_DISTANCE);
  }
  delay(100);
}

void runDisco() {
  // runServo();
  runLCDDisplay();
  runBuzzer();
}

void runServo() {
  int time = random(0, 15);
  for (servo_angle = 0; servo_angle <= 180; servo_angle += 1) {
    servo.write(servo_angle);
    delay(time);
  }
  for (servo_angle = 180; servo_angle >= 0; servo_angle -= 1) {
    servo.write(servo_angle);
    delay(time);
  }
}

void runLCDDisplay() {
  lcd.backlight();
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print(lcd_line1);
  lcd.setCursor(3,1);
  lcd.print(lcd_line2);
}

void runBuzzer() {
  firstSection();
  secondSection();
 
  //Variant 1
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);
  delay(500);
  secondSection();
 
  //Variant 2
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  
 
  delay(650);
}

void firstSection() {
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
  delay(500);
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
  delay(500);
}
 
void secondSection() {
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
  delay(325);
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
  delay(350);
}

void beep(int note, int duration) {
  tone(BUZZER, note, buzzerTempo / duration);
  delay(buzzerTempo / duration);
  if(buzzerCounter % 2 == 0) {
    delay(duration);
  } else {
    delay(duration);
  }
  noTone(BUZZER);
  delay(50);
  buzzerCounter++;
}

/*
 * MOTOR FUNCTIONALITY
 */





/*
 * IR Functionality
 */

 void readSensor() {
  Serial.print(++hitCount);
  Serial.write(" We have been hit!\n");
  Serial1.write(HIT);
}

/*
 * Car Manupulation Commands
 */

void handleState(char state) {
  Serial.println("Handling state...");
  Serial.println(state);
  if (state == 'u') {
    goForward();
  } else if (state =='d') {
    goBackward();
  } else if (state == 'l') {
    goLeft();
  } else if (state == 'r') {
    goRight();
  } else if (state == 'f') {
    fire();
  } else if (state == 's') {
    stopGoing();
  }
}

void enableM(byte motor) {
  if (motor == M1) {
    analogWrite(M1_ENA, m1_spd);
  } else if (motor == M2) {
    analogWrite(M2_ENA, m2_spd);
  }
}

void startM1() {
  if (m1_dir == FWD) {
    digitalWrite(M1_FWD, HIGH);
    digitalWrite(M1_REV, LOW);
  } else if (m1_dir == REV) {
    digitalWrite(M1_FWD, LOW);
    digitalWrite(M1_REV, HIGH);
  }
}

void startM2() {
  if (m2_dir == FWD) {
    digitalWrite(M2_FWD, HIGH);
    digitalWrite(M2_REV, LOW);
  } else if (m2_dir == REV) {
    digitalWrite(M2_FWD, LOW);
    digitalWrite(M2_REV, HIGH);
  }
}

void goForward() {
  m1_spd = MAX_SPEED;
  m2_spd = MAX_SPEED;
  m1_dir = FWD;
  m2_dir = FWD;
  enableM(M1);
  enableM(M2);
  startM1();
  startM2();
}

void goBackward() {
  m1_spd = MAX_SPEED;
  m2_spd = MAX_SPEED;
  m1_dir = REV;
  m2_dir = REV;
  enableM(M1);
  enableM(M2);
  startM1();
  startM2();
}

void goLeft() {
  m1_spd = 5;
  m2_spd = MAX_SPEED;
  enableM(M1);
  enableM(M2);
  startM1();
  startM2();
}

void goRight() {
  m1_spd = MAX_SPEED;
  m2_spd = 5;
  enableM(M1);
  enableM(M2);
  startM1();
  startM2();
}

void disableM(byte motor) {
  if (motor == M1) {
    digitalWrite(M1_ENA, 0);
  } else if (motor == M2) {
    digitalWrite(M2_ENA, 0);
  }
}

void stopGoing() {
  disableM(M1);
  disableM(M2);
}

void fire() {
  while (hitCount < SHOOT_COUNT) {
    digitalWrite(IR1_T, HIGH);
    digitalWrite(IR2_T, HIGH);
    delay(5);
    digitalWrite(IR1_T, LOW);
    digitalWrite(IR2_T, LOW);
    delay(1000);
    hitCount++;
  }
  hitCount = 0;
}
