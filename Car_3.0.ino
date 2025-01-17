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

#define LF_BI1 42
#define LF_BI2 43
#define LF_PWM 9

#define LR_BI1 39
#define LR_BI2 29
#define LR_PWM 5

int deadzone = 20;
int x1, x2, y1;
int x1_mid = 477;
int x2_mid = 498;
int y1_mid = 490;
int min = 0;
int max = 977;

void control(int BI1, int BI2, int pwm, int speed){
  if (speed >= 0){
    digitalWrite(BI1, 1);
    digitalWrite(BI2, 0);
    analogWrite(pwm, speed);
  }else if (speed < 0){
    digitalWrite(BI1, 0);
    digitalWrite(BI2, 1);
    analogWrite(pwm, abs(speed));
  }
}

void Setdeadzone(int a, int b, byte c){
  if (abs(a - b) < deadzone){
    a = b;
  }else{
    a = analogRead(c);
  }
}

void setup(){
  pinMode(RF_BI1, OUTPUT);
  pinMode(RF_BI2, OUTPUT);
  pinMode(RF_PWM, OUTPUT);

  pinMode(RR_BI1, OUTPUT);
  pinMode(RR_BI2, OUTPUT);
  pinMode(RR_PWM, OUTPUT);

  pinMode(LF_BI1, OUTPUT);
  pinMode(LF_BI2, OUTPUT);
  pinMode(LF_PWM, OUTPUT);
  
  pinMode(LR_BI1, OUTPUT);
  pinMode(LR_BI2, OUTPUT);
  pinMode(LR_PWM, OUTPUT);
  Serial.begin(19200);
}

void loop(){
  x1 = analogRead(joy1X);
  y1 = analogRead(joy1Y);
  x2 = analogRead(joy2X);

  Setdeadzone(x1, x1_mid, joy1X);
  Setdeadzone(x2, x2_mid, joy2X);
  Setdeadzone(y1, y1_mid, joy1Y);

  int speed_x1 = map(x1, min, max, -200, 200);
  int speed_x2 = map(x2, min, max, -200, 200);
  int speed_y1 = map(y1, min, max, -200, 200);

  int speed_RF = speed_y1 - speed_x1 - speed_x2; 
  int speed_RR = speed_y1 + speed_x1 - speed_x2; 
  int speed_LF = speed_y1 + speed_x1 + speed_x2; 
  int speed_LR = speed_y1 - speed_x1 + speed_x2; 

  control(RF_BI1, RF_BI2, RF_PWM, constrain(speed_RF, -200, 200));
  control(RR_BI1, RR_BI2, RR_PWM, constrain(speed_RR, -200, 200));
  control(LF_BI1, LF_BI2, LF_PWM, constrain(speed_LF, -200, 200));
  control(LR_BI1, LR_BI2, LR_PWM, constrain(speed_LR, -200, 200));
}
