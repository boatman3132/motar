// motor.cpp
#include "motor.h"
#include <Arduino.h>

Motor::Motor() {
    heart_rate = 60;  // 固定心率為 60 RPM
    servo_start_angle = 150;
    servo_rotate_angle = 5;
    servo_rotate_time = 0.025;
    
    // 初始化非阻塞控制相關變數
    currentPosition = servo_start_angle;
    servoState = WAITING;
    servoMoveStartTime = 0;
    cycleStartTime = 0;
    
    // 初始化快取變數
    lastHeartRate = -1;
    cachedWaitTime = 0;
    cachedMoveTime = 0;
}

void Motor::begin(int pin) {
    myServo.attach(pin);
    servoMoveStartTime = millis();
    cycleStartTime = millis();
    lastUpdateTime = millis();
}

void Motor::updateTimings() {
    if (lastHeartRate != heart_rate) {
        float totalCycleTime = (60.0/heart_rate) * 1000;
        cachedMoveTime = servo_rotate_time * 2 * servo_rotate_angle * 1000;
        cachedWaitTime = totalCycleTime - cachedMoveTime;
        lastHeartRate = heart_rate;
    }
}

void Motor::update() {
    unsigned long currentMillis = millis();
    
    // 降低更新頻率
    if (currentMillis - lastUpdateTime < UPDATE_INTERVAL) {
        return;
    }
    lastUpdateTime = currentMillis;

    updateTimings();

    // 伺服馬達非阻塞控制邏輯
    switch (servoState) {
        case MOVING_UP:
        case MOVING_DOWN:
            if (currentMillis - servoMoveStartTime >= servo_rotate_time * 1000) {
                servoMoveStartTime = currentMillis;
                
                if (servoState == MOVING_UP) {
                    currentPosition++;
                    if (currentPosition >= servo_start_angle + servo_rotate_angle) {
                        servoState = MOVING_DOWN;
                    }
                } else {
                    currentPosition--;
                    if (currentPosition <= servo_start_angle) {
                        servoState = WAITING;
                        cycleStartTime = currentMillis;
                    }
                }
                
                myServo.write(currentPosition);
            }
            break;

        case WAITING:
            if (currentMillis - cycleStartTime >= cachedWaitTime) {
                servoState = MOVING_UP;
                currentPosition = servo_start_angle;
                servoMoveStartTime = currentMillis;
            }
            break;
    }
}

void Motor::setHeartRate(int rate) {
    if (rate != heart_rate) {
        heart_rate = rate;
        updateTimings();
    }
}

float Motor::getHeartRate() const {
    return heart_rate;
}