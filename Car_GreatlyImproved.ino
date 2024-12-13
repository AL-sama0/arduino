#define joy1X A10
#define joy1Y A11
#define joy2X A15
#define joy2Y A14

#define RF_BI1 34
#define RF_BI2 35
#define RF_PWM 12

#define RR_BI1 37
#define RR_BI2 36
#define RR_PWM 8

#define LF_BI1 43
#define LF_BI2 42
#define LF_PWM 9

#define LR_BI1 29
#define LR_BI2 39
#define LR_PWM 5

int x1=0,y1=0,x2=0,y2=0;
int middle_x1=477, middle_y1=490, middle_x2=497, middle_y2=483;
int max=977;
int min=0;

void controlRF(int BI1,int BI2,int speed){
  if (speed >= 0) {
    digitalWrite(RF_BI1, BI1);
    digitalWrite(RF_BI2, BI2);
    analogWrite(RF_PWM, speed);
  }
  else if (speed < 0) {
    digitalWrite(RF_BI1, BI2);
    digitalWrite(RF_BI2, BI1);
    analogWrite(RF_PWM, abs(speed));
  }
}

void controlLF(int BI2,int BI1,int speed){
  if (speed >= 0) {
    digitalWrite(LF_BI1, BI1);
    digitalWrite(LF_BI2, BI2);
    analogWrite(LF_PWM, speed);
  }
  else if (speed < 0) {
    digitalWrite(LF_BI1, BI2);
    digitalWrite(LF_BI2, BI1);
    analogWrite(LF_PWM, abs(speed));
  }
}

void controlRR(int BI1,int BI2,int speed){
  if (speed >= 0) {
    digitalWrite(RR_BI1, BI1);
    digitalWrite(RR_BI2, BI2);
    analogWrite(RR_PWM, speed);
  }
  else if (speed < 0) {
    digitalWrite(RR_BI1, BI2);
    digitalWrite(RR_BI2, BI1);
    analogWrite(RR_PWM, abs(speed));
  }
}

void controlLR(int BI2,int BI1,int speed){
  if (speed >= 0) {
    digitalWrite(LR_BI1, BI1);
    digitalWrite(LR_BI2, BI2);
    analogWrite(LR_PWM, speed);
  }
  else if (speed < 0) {
    digitalWrite(LR_BI1, BI2);
    digitalWrite(LR_BI2, BI1);
    analogWrite(LR_PWM, abs(speed));
  }
}

void setup() {
  pinMode(RF_PWM,OUTPUT);
  pinMode(RR_PWM,OUTPUT);
  pinMode(LF_PWM,OUTPUT);
  pinMode(LR_PWM,OUTPUT);

  pinMode(RF_BI1,OUTPUT);
  pinMode(RF_BI2,OUTPUT);
  pinMode(RR_BI1,OUTPUT);
  pinMode(RR_BI2,OUTPUT);
  pinMode(LF_BI1,OUTPUT);
  pinMode(LF_BI2,OUTPUT);
  pinMode(LR_BI1,OUTPUT);
  pinMode(LR_BI2,OUTPUT);
}

void loop() {
  x1 = analogRead(joy1X);
  y1 = analogRead(joy1Y);
  x2 = analogRead(joy2X);
  y2 = analogRead(joy2Y);

  int speed_1  = speed_y1 + speed_x1;
  int speed_2  = speed_y1 - speed_x1;

  int speed_y1 = map(y1, min, max, -200, 200);
  int speed_x1 = map(x1, min, max, -200, 200);
  int speed_x2 = map(x2, min, max, -200, 200);

  int speed_RF = speed_2 - speed_x2;
  int speed_RR = speed_1 - speed_x2;
  int speed_LF = speed_1 + speed_x2;
  int speed_LR = speed_2 + speed_x2;

  controlRF(1, 0, speed_RF);
  controlRR(1, 0, speed_RR);
  controlLF(1, 0, speed_LF);
  controlLR(1, 0, speed_LR);
}