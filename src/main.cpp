#include <Arduino.h>
#include <ESP32Servo.h>  // 使用 ESP32Servo 庫

Servo myServo;  // 宣告舵機物件

// 選擇 GPIO 21 作為舵機的信號腳位
#define SERVO_PIN 21

int heart_rate = 60; //RPM

void setup() {
  Serial.begin(115200);
  
  // 初始化舵機，連接到 GPIO 21
  myServo.attach(SERVO_PIN);

}

void loop() {
  // 範例：讓舵機從 0 度移動到 180 度
  for (int pos = 0; pos <= 3; pos += 1) {
    myServo.write(pos);  // 設定舵機位置
    delay(15);           // 確保舵機有足夠時間移動
  }

  // 再讓舵機從 180 度移動回 0 度
  for (int pos = 3; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(15);
  }
  delay(60000/heart_rate-15*6);
}
