#include <Arduino.h>
#include <ESP32Servo.h>  // 使用 ESP32Servo 庫

Servo myServo;  // 宣告舵機物件

// 選擇 GPIO 1 作為舵機的信號腳位
#define SERVO_PIN 1

int heart_rate = 60; //RPM

// 舵機參數
int servo_start_angle = 45; //旋轉起始角度
int servo_rotate_angle = 5; //旋轉角度
int servo_rotate_time = 15; //旋轉時間（ms）


void setup() {
  Serial.begin(115200);
  
  // 初始化舵機，連接到 GPIO 1
  myServo.attach(SERVO_PIN);

}

void loop() {
  // 範例：讓舵機從 0 度移動到 180 度
  for (int pos = servo_start_angle ; pos <= (servo_start_angle + servo_rotate_angle) ; pos += 1) {
    myServo.write(pos);  // 設定舵機位置
    delay(servo_rotate_time);           // 確保舵機有足夠時間移動
  }

  // 再讓舵機從 180 度移動回 0 度
  for (int pos = servo_start_angle + servo_rotate_angle; pos >= servo_start_angle; pos -= 1) {
    myServo.write(pos);
    delay(servo_rotate_time);
  }
  delay(60000/heart_rate - servo_rotate_time * 2 * servo_rotate_angle);
}
