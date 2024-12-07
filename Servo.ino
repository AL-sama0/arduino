#include <Servo.h>
int n=-1;
Servo myservo;

void setup() {
  myservo.attach(9);
  myservo.write(0);

  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("Start working");
  Serial.println("1=Reload  0=Reset");
}

void loop() {
  if(Serial.available()){
    n=Serial.read()-48;
  }
  if(n==1){
    Serial.println("Reload");
    myservo.write(90);
    delay(750);
    myservo.write(0);
  }
  if(n==0){
    Serial.println("Reset");
    myservo.write(0);
  }
  n=-1;
}