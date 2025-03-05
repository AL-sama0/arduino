#include <SoftwareSerial.h>
SoftwareSerial Serial1(2,3);
String read;
String output;
String username;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.print("Please enter the username: ");
  while(true){
    if(Serial.available()){
      username = Serial.readStringUntil('~');
      Serial.println(username.c_str());
      break;
    }
  }
}

void loop(){
  if(Serial.available()){
    read = Serial.readString();
    output = username + ": " + read;
    Serial.print(output.c_str());
    Serial1.write(output.c_str());
  }

  if(Serial1.available()){
    Serial.print(Serial1.readString());
  }
}
