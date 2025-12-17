#define JOYSTICK1_X A2
#define JOYSTICK1_Y A3
#define JOYSTICK2_X A4
#define JOYSTICK2_Y A5
#define TRIGGER1 A6
#define TRIGGER2 A7
#define TRIGGER3 A8
#define TRIGGER4 A9
#define EVEN_CHECKMODE 0
#define ODD_CHECKMODE 1

const int buttonPin[] = {37, 36, 35, 34, 33, 32, 31, 30};
const int switchPin[] = {22, 23, 24, 25, 26, 27, 28, 29};
int switchValue[8] = {0};
int buttonValue[8] = {0};
int trigger1, trigger2, trigger3, trigger4 = 0;

const int max=1300;
const int min=100;

int parity_check(int data, int mode) 
{
  int count = 0;
  unsigned int unsigned_data = (unsigned int)data;
    
  for (int i = 0; i < sizeof(int) * 8; i++) 
  {
    count += (unsigned_data >> i) & 0x01;
  }
    
  if (mode == 0) 
  { 
    return (count % 2 == 0) ? 0 : 1;
  } 
  else 
  { 
    return (count % 2 == 0) ? 1 : 0;
  }
}

void sendSpeedDataToSlave(int data)
{
  if (data > 0)
  {
    Serial3.write(1);
    int body = floor(data);

    Serial3.write(body);
  }
  if (data < 0)
  {
    Serial3.write(0);
    int body = ceil(data);
        
    Serial3.write(abs(body))
  }
  if (data == 0)
  {
    Serial3.write(0);
    Serial3.write(0);
  }
}

void sendBigDataToSlave(int data)
{
  int count = 5;
  while(data > 255)
  {
    Serial3.write(255);
    data = data - 255;
    count --;
  }

  Serial3.write(data);
  count --;

  if (count != 0)
  {
    for (int i = 0; i < count; i ++)
    {
      Serial3.write(0);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(9600);

  for (int i = 0; i < 8; i ++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
  for (int i = 0; i < 8; i ++) {
    pinMode(switchPin[i], INPUT_PULLUP);
  }
}

void loop() {
  int x1 = analogRead(JOYSTICK1_X);
  int y1 = analogRead(JOYSTICK1_Y);
  int x2 = analogRead(JOYSTICK2_X);
  int y2 = analogRead(JOYSTICK2_Y);

  int speed_x1 = map(x1, min, max, -200, 200);
  int speed_x2 = map(x2, min, max, -200, 200);
  int speed_y1 = map(y1, min, max, -200, 200);

  int speed_RF = speed_y1 - speed_x1 - speed_x2; 
  int speed_RR = speed_y1 + speed_x1 - speed_x2; 
  int speed_LF = speed_y1 + speed_x1 + speed_x2; 
  int speed_LR = speed_y1 - speed_x1 + speed_x2; 

  speed_RF = constrain(speed_RF, -200, 200);
  speed_RR = constrain(speed_RR, -200, 200);
  speed_LF = constrain(speed_LF, -200, 200);
  speed_LR = constrain(speed_LR, -200, 200);

  int switch_sum = 0;
  for (int i = 0; i < 8; i ++) {
    switchValue[i] = digitalRead(switchPin[i]);
    switch_sum += switchValue[i];
  }
  int button_sum = 0;
  for (int i = 0; i < 8; i ++) {
    buttonValue[i] = digitalRead(buttonPin[i]);
    button_sum += buttonValue[i];
  }

  trigger1 = analogRead(TRIGGER1);
  trigger2 = analogRead(TRIGGER2);
  trigger3 = analogRead(TRIGGER3);
  trigger4 = analogRead(TRIGGER4);

  Serial3.write(0xAA);

  for (int i = 0; i < 8; i ++) {
    Serial3.write(switchValue[i]);
  }
  for (int i = 0; i < 8; i ++) {
    Serial3.write(buttonValue[i]);
  }

  sendSpeedDataToSlave(speed_RF);
  sendSpeedDataToSlave(speed_RR);
  sendSpeedDataToSlave(speed_LF);
  sendSpeedDataToSlave(speed_LR);

  // int verify = (abs(speed_RF) + abs(speed_RR) + abs(speed_LF) + abs(speed_LR)) / 4;
  // Serial3.write(verify);

  sendBigDataToSlave(trigger1);
  sendBigDataToSlave(trigger2);
  sendBigDataToSlave(trigger3);
  sendBigDataToSlave(trigger4);

  int even_verify = parity_check(switch_sum + button_sum + speed_RF + speed_RR + speed_LF + speed_LR + trigger1 + trigger2 + trigger3 + trigger4, EVEN_CHECKMODE);
  int odd_verify = parity_check(switch_sum + button_sum + speed_RF + speed_RR + speed_LF + speed_LR + trigger1 + trigger2 + trigger3 + trigger4, ODD_CHECKMODE);
  Serial3.write(even_verify);
  Serial3.write(odd_verify);

  Serial.print(" Verify code: ");
  Serial.print(even_verify);·
  Serial.print(" ");
  Serial.print(odd_verify);
  Serial.println();

  Serial3.write(0xFF);
}
