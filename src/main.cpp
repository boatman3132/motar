#include <Arduino.h>
#include "motor.h"

Motor motor;

void setup() {
    Serial.begin(9600);
    motor.begin(1);  // 使用 GPIO 1
}

void loop() {
    motor.update();
}