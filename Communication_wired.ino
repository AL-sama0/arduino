#include <SoftwareSerial.h>
String sd;
String rm;
SoftwareSerial Serial1(2,3);


void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop(){
  while(Serial.available()){
      Serial1.write(Serial.read());
      
  }

  
  while(Serial1.available()){
      char a = Serial1.read();
      Serial.print(a);
  }
}
