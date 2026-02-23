#include <Wire.h>

#define SLAVE_ADDRESS 0x08

void receiveEvent(int bytes) {
  Serial.print("Received Message: ");
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  // I2C Slave
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  Serial.println("ESP32 I2C Slave Ready");
}

void loop() {
  delay(100);
}
