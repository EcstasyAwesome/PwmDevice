#include <PwmDevice.h>

PwmDevice device(3, 40, 230);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    byte value = Serial.readString().toInt();
    device.setPercent(value);
    Serial.print("pwm = ");
    Serial.print(device.getPwm());
    Serial.print(", percent = ");
    Serial.println(device.getPercent());
  }
}