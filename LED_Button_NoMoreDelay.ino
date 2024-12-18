#define LED_PIN1 8
#define LED_PIN2 9
#define LED_PIN3 10
#define LED_PIN4 11
#define BUTTON_PIN 13

int x = 0, y = 0, z = 0;
unsigned long long time, t1 = 0, t2 = 0, t3 = 0;
int ledState = LOW;
int buttonState;
int lastButtonState = LOW;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  digitalWrite(LED_PIN4, 0);
}

void loop() {
  time = millis();
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(LED_PIN4, ledState);
  lastButtonState = reading;

  if ((time - t1) == 1000) {
    x = 1 - x;
    t1 = millis();
    digitalWrite(LED_PIN1, x);
  }

  if ((time - t2) == 2000) {
    y = 1 - y;
    t2 = millis();
    digitalWrite(LED_PIN2, y);
  }

  if ((time - t3) == 3000) {
    z = 1 - z;
    t3 = millis();
    digitalWrite(LED_PIN3, z);
  }

}
