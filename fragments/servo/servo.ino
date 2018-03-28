#include <stdio.h>
#include <stdlib.h>

#define M3_ANGLE 10

void setup()
{
  pinMode(M3_ANGLE, OUTPUT);
  //randomSeed(analogRead(A0));
  reset();
}


void loop()
{
  generator();
  delay(300);
}

  void reset(){
    digitalWrite(13, LOW);
  }
  
  void generator(){
    // int time = random(1, 5);
    //int time =(analogRead(1)%100)*10+1000;
    int time = random(500,6000);

     
    if( digitalRead(13) == HIGH )      
      digitalWrite(13, LOW);  
    else
        digitalWrite(13, HIGH);
    
    delay(time);
    // delay(time*1000);
  }





