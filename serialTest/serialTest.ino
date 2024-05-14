#define LED_1 12
#define LED_2 27

TaskHandle_t task1; // blink LED_1
TaskHandle_t task2; // controle do LED 2 por serial

void blinkBranco (void *pvParameters) {
  while(1) {
    digitalWrite(LED_1, HIGH);
    delay(250);
    digitalWrite(LED_1, LOW);
    delay(250);
  }
}

void controlVermelho (void *pvParameters) {
  while(1) {
    if(Serial.available()) {
      char c = Serial.read();
      if (c == 'a') {
        digitalWrite(LED_2, HIGH);
        Serial.println("ON");
      }
      else if (c == 'b') {
        digitalWrite(LED_2, LOW);
        Serial.println("OFF");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  xTaskCreatePinnedToCore(blinkBranco, "task1", 10000, NULL, 0, &task1, 0);
  xTaskCreatePinnedToCore(controlVermelho, "task2", 10000, NULL, 1, &task2, 1);

}

void loop() {
  // put your main code here, to run repeatedly:

}
