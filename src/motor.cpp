// motor.cpp
#include "motor.h"
#include <Arduino.h>

Motor::Motor() {
    heart_rate = 30;
    servo_start_angle = 45;
    servo_rotate_angle = 5;
    servo_rotate_time = 0.015;
    heart_rate_min = heart_rate;
    seconds_elapsed = 0;
    
    // 初始化非阻塞控制相關變數
    currentPosition = servo_start_angle;
    servoState = WAITING;
    servoMoveStartTime = 0;
    cycleStartTime = 0;
}

void Motor::begin(int pin) {
    myServo.attach(pin);
    previousMillis = millis();
    servoMoveStartTime = millis();
    cycleStartTime = millis();
}

void Motor::update() {
    unsigned long currentMillis = millis();

    // 心率更新邏輯
    if (currentMillis - previousMillis >= interval * 1000) {
        previousMillis = currentMillis;
        seconds_elapsed += interval;
        
        if (seconds_elapsed <= seconds_elapsed_max - interval) {
            heart_rate += heart_rate_increase;
            Serial.print("心率更新為: ");
            Serial.println(heart_rate);
        }
    }

    if (seconds_elapsed >= seconds_elapsed_max) {
        heart_rate = heart_rate_min;
        seconds_elapsed = 0;
        Serial.println("重新開始循環");
    }

    // 伺服馬達非阻塞控制邏輯
    switch (servoState) {
        case MOVING_UP:
            if (currentMillis - servoMoveStartTime >= servo_rotate_time * 1000) {
                servoMoveStartTime = currentMillis;
                currentPosition++;
                myServo.write(currentPosition);
                
                if (currentPosition >= servo_start_angle + servo_rotate_angle) {
                    servoState = MOVING_DOWN;
                }
            }
            break;

        case MOVING_DOWN:
            if (currentMillis - servoMoveStartTime >= servo_rotate_time * 1000) {
                servoMoveStartTime = currentMillis;
                currentPosition--;
                myServo.write(currentPosition);
                
                if (currentPosition <= servo_start_angle) {
                    servoState = WAITING;
                    cycleStartTime = currentMillis;
                }
            }
            break;

        case WAITING:
            // 計算等待時間：總週期減去運動時間
            float totalCycleTime = (60.0/heart_rate) * 1000;
            float moveTime = servo_rotate_time * 2 * servo_rotate_angle * 1000;
            float waitTime = totalCycleTime - moveTime;
            
            if (currentMillis - cycleStartTime >= waitTime) {
                servoState = MOVING_UP;
                currentPosition = servo_start_angle;
                servoMoveStartTime = currentMillis;
            }
            break;
    }
}

void Motor::setHeartRate(int rate) {
    heart_rate = rate;
    heart_rate_min = rate;  // 更新最小心率
}