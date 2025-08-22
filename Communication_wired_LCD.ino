#include <SoftwareSerial.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

SoftwareSerial Serial1(2,3);

hd44780_I2Cexp lcd;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);

  lcd.begin(20,4);
  lcd.clear();
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print("Send:");
  lcd.setCursor(0,2);
  lcd.print("Received:");
  
  while(Serial.available()){
    lcd.clear();
    String s = Serial.readStringUntil('\n');
    Serial1.write(s.c_str()); 
    lcd.setCursor(0,0);
    lcd.print("Send:");
    lcd.setCursor(0,2);
    lcd.print("Received:");
    lcd.setCursor(5,0);
    lcd.print(s);
  }
  
  while(Serial1.available()){
    lcd.clear();
    String r = Serial1.readStringUntil('\n');
    lcd.setCursor(0,0);
    lcd.print("Send:");
    lcd.setCursor(0,2);
    lcd.print("Received:");
    lcd.setCursor(9,2);
    lcd.print(r);
  }
}
