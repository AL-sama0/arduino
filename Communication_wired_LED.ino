#include <SoftwareSerial.h>
SoftwareSerial Serial1(2,3);
String a = "?";

#define LEDPIN 6

void StartReceiving(){
  while(Serial1.available()){
    a = Serial1.readStringUntil('\n');
    Serial.println(a);
  }
}
void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  Serial.println("Finish Setup!");
}

void loop(){
  StartReceiving();

  if(a == "o"){
    digitalWrite(LEDPIN, HIGH);
    Serial1.write("LED is turned on!\n");
  }

  if(a == "c"){
    digitalWrite(LEDPIN, LOW);
    Serial1.write("LED is turned off!\n");
  }

  if(a == "b"){
    Serial1.write("Enter breathing light mode!\n");

    while(true){
      StartReceiving();
      if(a == "b"){
        for(int i = 1; i <= 225; i++){
          analogWrite(LEDPIN, i);
          delay(8);
        }

        for(int i = 225; i >= 1; i--){
          analogWrite(LEDPIN, i);
          delay(8);
        }
      } else if(a == "q"){
        digitalWrite(LEDPIN, LOW);
        Serial1.write("Quit breathing light mode!");
        break;
      }
    }
  }
  a = "?";
}
