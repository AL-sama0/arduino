//Please add library JY901.h before using this code

#include <JY901.h> // 引入JY901库

// 定义电机控制的引脚
#define RF_BI1 34 // 右前轮控制引脚1
#define RF_BI2 35 // 右前轮控制引脚2
#define RF_PWM 12 // 右前轮PWM引脚

#define RR_BI1 37 // 右后轮控制引脚1
#define RR_BI2 36 // 右后轮控制引脚2
#define RR_PWM 8  // 右后轮PWM引脚

#define LF_BI1 43 // 左前轮控制引脚1
#define LF_BI2 42 // 左前轮控制引脚2
#define LF_PWM 9  // 左前轮PWM引脚

#define LR_BI1 29 // 左后轮控制引脚1
#define LR_BI2 39 // 左后轮控制引脚2
#define LR_PWM 5  // 左后轮PWM引脚

double getYaw = 0; // 当前偏航角
int speed = 0;     // 控制速度

// PID控制参数
double kp = 1.0;     // 比例增益
double ki = 0.1;     // 积分增益
double kd = 0.05;    // 微分增益

double error = 0;          // 当前误差
double previousError = 0;  // 前一次误差
double integral = 0;       // 误差积分
double derivative = 0;     // 误差微分
double setpoint = 0;       // 期望的偏航角

unsigned long currentTime = 0;   // 当前时间
unsigned long previousTime = 0;  // 前一次时间
double deltaTime = 0;            // 时间差（秒）

double maxIntegral = 1000; // 积分限制，防止积分饱和

void setup() {
  // 初始化电机控制引脚
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

  Serial.begin(9600);    // 初始化串口通讯
  Serial3.begin(9600);   // 初始化Serial3通讯
  JY901.attach(Serial3); // 连接JY901传感器到Serial3

  previousTime = millis(); // 初始化前一次时间
}

void controlRF(int BI1, int BI2, int speed) {
  // 控制右前轮电机的旋转方向和速度
  if (speed > 0) { // 正转
    digitalWrite(RF_BI1, BI1);
    digitalWrite(RF_BI2, BI2);
    analogWrite(RF_PWM, abs(speed));
  } else if (speed < 0) { // 反转
    digitalWrite(RF_BI1, BI2);
    digitalWrite(RF_BI2, BI1);
    analogWrite(RF_PWM, abs(speed));
  }
}

void controlRR(int BI1, int BI2, int speed) {
  // 控制右后轮电机的旋转方向和速度
  if (speed > 0) { // 正转
    digitalWrite(RR_BI1, BI1);
    digitalWrite(RR_BI2, BI2);
    analogWrite(RR_PWM, abs(speed));
  } else if (speed < 0) { // 反转
    digitalWrite(RR_BI1, BI2);
    digitalWrite(RR_BI2, BI1);
    analogWrite(RR_PWM, abs(speed));
  }
}

void controlLF(int BI1, int BI2, int speed) {
  // 控制左前轮电机的旋转方向和速度
  if (speed < 0) { // 反转
    digitalWrite(LF_BI1, BI1);
    digitalWrite(LF_BI2, BI2);
    analogWrite(LF_PWM, abs(speed));
  } else if (speed > 0) { // 正转
    digitalWrite(LF_BI2, BI1);
    digitalWrite(LF_BI1, BI2);
    analogWrite(LF_PWM, abs(speed));
  }
}

void controlLR(int BI1, int BI2, int speed) {
  // 控制左后轮电机的旋转方向和速度
  if (speed < 0) { // 反转
    digitalWrite(LR_BI2, BI2);
    digitalWrite(LR_BI1, BI1);
    analogWrite(LR_PWM, abs(speed));
  } else if (speed > 0) { // 正转
    digitalWrite(LR_BI2, BI1);
    digitalWrite(LR_BI1, BI2);
    analogWrite(LR_PWM, abs(speed));
  }
}

void loop() {
  currentTime = millis();                       // 获取当前时间（毫秒）
  deltaTime = (currentTime - previousTime) / 1000.0; // 计算时间差，转换为秒

  if (deltaTime <= 0) {
    deltaTime = 0.001; // 防止deltaTime为零或负值
  }
  
  JY901.receiveSerialData(); // 接收JY901传感器数据
  getYaw = JY901.getYaw();   // 获取当前偏航角

  // 计算PID控制
  error = setpoint - getYaw;                       // 计算当前误差
  integral += error * deltaTime;                   // 计算误差积分
  integral = constrain(integral, -maxIntegral, maxIntegral); // 限制积分误差，防止积分饱和
  derivative = (error - previousError) / deltaTime; // 计算误差微分
  speed = kp * error + ki * integral + kd * derivative; // 计算控制输出速度
  speed = constrain(speed, -255, 255);

  previousError = error;        // 更新前一次误差
  previousTime = currentTime;   // 更新前一次时间
  Serial.print("Speed: ");
  Serial.println(speed); // 打印当前偏航角到串口

  // 控制电机速度和方向
  controlRF(1, 0, speed); // 控制右前轮
  controlRR(1, 0, speed); // 控制右后轮
  controlLF(1, 0, -speed);  // 控制左前轮
  controlLR(1, 0, -speed);  // 控制左后轮
}
