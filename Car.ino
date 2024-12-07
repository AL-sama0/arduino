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
int deadzone=40;

void controlRF(int BI1,int BI2,int speed){
  digitalWrite(RF_BI1, BI1);
  digitalWrite(RF_BI2, BI2);
  analogWrite(RF_PWM, speed);
}

void controlLF(int BI2,int BI1,int speed){
  digitalWrite(LF_BI1, BI1);
  digitalWrite(LF_BI2, BI2);
  analogWrite(LF_PWM, speed);
}

void controlRR(int BI1,int BI2,int speed){
  digitalWrite(RR_BI1, BI1);
  digitalWrite(RR_BI2, BI2);
  analogWrite(RR_PWM, speed);
}

void controlLR(int BI2,int BI1,int speed){
  digitalWrite(LR_BI1, BI1);
  digitalWrite(LR_BI2, BI2);
  analogWrite(LR_PWM, speed);
}

void setup() {
  Serial.begin(9600);
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
    x1=analogRead(joy1X);
    y1=analogRead(joy1Y);
    x2=analogRead(joy2X);
    y2=analogRead(joy2Y);

    Serial.print("x1: ");
    Serial.print(x1);
    Serial.print(" y1: ");
    Serial.print(y1);
    Serial.print(" x2: ");
    Serial.print(x2);
    Serial.print(" y2: ");
    Serial.print(y2);
    Serial.println();

    if(x1 > (middle_x1 - deadzone) && x1 < (middle_x1 + deadzone) && y1 > (middle_y1 + deadzone)){//Forward
      int speed = map(y1, middle_y1, max, 0, 200);
      controlRF(1, 0, speed);
      controlRR(1, 0, speed);
      controlLF(1, 0, speed);
      controlLR(1, 0, speed);
    }

    if(x1 > (middle_x1 - deadzone) && x1 < (middle_x1 + deadzone) && y1 < (middle_y1 - deadzone)){//Backward
      int speed = map(y1, middle_y1, min, 0, 200);
      controlRF(0, 1, map(y1, middle_y1, min, 0, 200));
      controlRR(0, 1, map(y1, middle_y1, min, 0, 200));
      controlLF(0, 1, map(y1, middle_y1, min, 0, 200));
      controlLR(0, 1, map(y1, middle_y1, min, 0, 200));
    }

    if(y1 > (middle_y1 - deadzone) && y1 < (middle_y1 + deadzone) && x1 < (middle_x1 - deadzone)){//Leftward
      int speed = map(x1, middle_x1, min, 0, 200);
      controlRF(1, 0, speed);
      controlRR(0, 1, speed);
      controlLF(0, 1, speed);
      controlLR(1, 0, speed);
    }

    if(y1 > (middle_y1 - deadzone) && y1 < (middle_y1 + deadzone) && x1 > (middle_x1 + deadzone)){//Rightward
      int speed = map(x1, middle_x1, max, 0, 200);
      controlRF(0, 1, speed);
      controlRR(1, 0, speed);
      controlLF(1, 0, speed);
      controlLR(0, 1, speed);
    }

    if(y2 > (middle_y2 - deadzone) && y2 < (middle_y2 + deadzone) && x2 < (middle_x2 - deadzone)){//Left
      int speed = map(x2, middle_x2, min, 0, 200);
      controlRF(1, 0, speed);
      controlRR(1, 0, speed);
      controlLF(0, 1, speed);
      controlLR(0, 1, speed);
    }

    if(y2 > (middle_y2 - deadzone) && y2 < (middle_y2 + deadzone) && x2 > (middle_x2 + deadzone)){//Right
      int speed = map(x2, middle_x2, max, 0, 200);
      controlRF(0, 1, speed);
      controlRR(0, 1, speed);
      controlLF(1, 0, speed);
      controlLR(1, 0, speed);
    }

    if(x1 > (middle_x1 - deadzone) && x1 < (middle_x1 + deadzone) && y1 < (middle_y1 + deadzone) && y1 > (middle_y1 - deadzone) && x2 > (middle_x2 - deadzone) && x2 < (middle_x2 + deadzone) && y2 < (middle_y2 + deadzone) && y2 > (middle_y2 - deadzone)){//Stop
      controlRF(1, 0, 0);
      controlRR(1, 0, 0);
      controlLF(1, 0, 0);
      controlLR(1, 0, 0);
    }
}