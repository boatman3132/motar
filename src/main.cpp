#include <Arduino.h>
#include <Stepper.h>

// 定義步進馬達的步數
const int stepsPerRevolution = 2048; // 28BYJ-48 的步數

// 初始化 Stepper 物件
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // 設定馬達速度（每分鐘轉速）
  myStepper.setSpeed(5); // 5 RPM
}

void loop() {
  // 讓馬達順時針旋轉圈
  myStepper.step(stepsPerRevolution * 0.002);
  delay(100); // 等待一秒

  // 讓馬達逆時針旋轉圈
  myStepper.step(-stepsPerRevolution * 0.002);
  delay(1100); // 等待一秒
}