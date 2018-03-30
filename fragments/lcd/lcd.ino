//Written by Nick Koumaris 
//info@educ8s.tv 
//educ8s.tv

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup()  
{
  Serial.begin(9600);
  lcd.backlight();
  lcd.begin(16,2); // Initialize LCD
  lcd.setCursor(0,0); // Set the cursor at the 4th column and 1st row
  lcd.print("Pietje Pek!");
  Serial.write("Hello YouTube!\n");
  lcd.setCursor(8,1);  // Set the cursor at the 9th column and 2nd row
  lcd.print("****");
  Serial.write("****\n");
  lcd.setCursor(0,2);  // Set the cursor at the 1st column and 3rd row
  lcd.print("Lets win on Friday!");
  Serial.write("This is a demo text\n");
  lcd.setCursor(8,3);  // Set the cursor at the 9th column and 4th row
  lcd.print("****");
  Serial.write("****\n");
}

void loop() 
{ 

}
