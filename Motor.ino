String input;
int speed;
void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(9600);
  Serial.println("Work");
}

void loop() {
  if(Serial.available()){
    input = Serial.readString();
    speed = input.toInt();
    Serial.println(speed);
  }

  if(speed<0){
    analogWrite(11, speed/-1);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
  }else{
    analogWrite(11, speed);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  }
}