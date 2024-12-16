#include <Arduino.h>
#include <ESP32Servo.h>  // 使用 ESP32Servo 庫



int heart_rate = 30; //起始心率

const long interval = 10; // 間隔秒數增加一次心率
int heart_rate_increase = 10; // 每次增加多少心率
int seconds_elapsed_max = 100; // 最大經過的秒數 之後重複循環

// 舵機參數
int servo_start_angle = 45; //旋轉起始角度
int servo_rotate_angle = 5; //旋轉角度
float servo_rotate_time = 0.015; //旋轉時間（秒）(原本15ms = 0.015秒)









Servo myServo;  // 宣告舵機物件
#define SERVO_PIN 1 // 選擇 GPIO 1 作為舵機的信號腳位
int heart_rate_min = heart_rate; // 起始心率重複循環
unsigned long previousMillis = 0; // 用於追蹤時間
int seconds_elapsed = 0; // 目前經過的秒數

void setup() {
  Serial.begin(9600);
  
  // 初始化舵機，連接到 GPIO 1
  myServo.attach(SERVO_PIN);
  
  // 初始化計時器
  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // 檢查是否經過指定的間隔時間
  if (currentMillis - previousMillis >= interval * 1000) { // 轉換為毫秒
    previousMillis = currentMillis;
    seconds_elapsed += interval;
    
    // 在設定的最大時間內增加心率
    if (seconds_elapsed <= seconds_elapsed_max - interval) {
      heart_rate += heart_rate_increase;
      Serial.print("心率更新為: ");
      Serial.println(heart_rate);
    }
  }

  // 如果超過設定的最大時間，重置程序
  if (seconds_elapsed >= seconds_elapsed_max) {
    heart_rate = heart_rate_min;
    seconds_elapsed = 0;
    Serial.println("重新開始循環");
  }

  // 舵機控制
  for (int pos = servo_start_angle; pos <= (servo_start_angle + servo_rotate_angle); pos += 1) {
    myServo.write(pos);
    delay(servo_rotate_time * 1000); // 轉換為毫秒
  }

  for (int pos = servo_start_angle + servo_rotate_angle; pos >= servo_start_angle; pos -= 1) {
    myServo.write(pos);
    delay(servo_rotate_time * 1000); // 轉換為毫秒
  }
  
  delay((60.0/heart_rate - servo_rotate_time * 2 * servo_rotate_angle) * 1000); // 轉換為毫秒
}