#define SDIST_TRIGGER 12        // Pin to send trigger pulse
#define SDIST_ECHO 13        // Pin to receive echo pulse 
  
void setup() 
{ 
  Serial.begin(9600); 
  pinMode(SDIST_ECHO, INPUT); 
  pinMode(SDIST_TRIGGER, OUTPUT); 
}

void loop() 
{ 
  // Start Ranging -Generating a trigger of 10us burst 
  digitalWrite(SDIST_TRIGGER, LOW); 
  delayMicroseconds(2); 
  digitalWrite(SDIST_TRIGGER, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(SDIST_TRIGGER, LOW);

  // Distance Calculation

  
  float distance = pulseIn(SDIST_ECHO, HIGH); 
  distance= distance/58; 

/* The speed of sound is 340 m/s or 29 us per cm.The Ultrasonic burst travels out & back.So to find the distance of object we divide by 58  */

  Serial.print(distance); 
  Serial.println(" cm");

  delay(200); 
}

