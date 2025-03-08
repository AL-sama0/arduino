#include <RF24.h>

#define ANTENNA_CSN 7
#define ANTENNA_CE 8

class WirelessConnect {
private:
    RF24 radio;
    const uint16_t address;  // 使用 uint64_t 存储地址

public:
    WirelessConnect(int cePin, int csnPin, uint64_t addr) 
        : radio(cePin, csnPin), address(addr) {}

    void InitConnect() {
        radio.begin();
        radio.setPALevel(RF24_PA_MIN);
        radio.setDataRate(RF24_2MBPS);
        radio.setChannel(0x4C);
    }

    bool SendMessage(const char* data) {
        radio.openWritingPipe(address);
        radio.stopListening();  // 切换到发送模式
        bool result = radio.write(data, strlen(data) + 1);  // 发送数据
        return result;
    }

    bool ReceiveMessage(char* buffer, uint8_t maxLen) {
        radio.openReadingPipe(0, address);
        radio.startListening();  // 切换到接收模式
        bool result = false;

        if (radio.available()) {
            radio.read(buffer, maxLen);  // 读取数据
            result = true;
        }
        return result;
    }
};

const uint16_t address = 0xF0F0;
WirelessConnect connect(ANTENNA_CE, ANTENNA_CSN, address);

void setup() {
    Serial.begin(9600);
    connect.InitConnect();
    Serial.println("Wireless Communication Initialized!");
}

void loop() {
    // 发送逻辑
    if (Serial.available() > 0) {
        static char buffer[50];
        int index = 0;

        while (Serial.available() > 0 && index < sizeof(buffer) - 1) {
            char c = Serial.read();
            if (c == '\n') {
                break;
            }
            buffer[index++] = c;
            delay(3);
        }
        buffer[index] = '\0';

        bool result = connect.SendMessage(buffer);
        if (result) {
            Serial.println("Message Sent: " + String(buffer));
        } else {
            Serial.println("Failed to Send Message.");
        }
    }

    // 接收逻辑
    char receiveBuffer[32];
    if (connect.ReceiveMessage(receiveBuffer, sizeof(receiveBuffer))) {
        Serial.print("Received Message: ");
        Serial.println(receiveBuffer);
    }

    delay(10);  // 短暂延时
}