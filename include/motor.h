// motor.h
#ifndef MOTOR_H
#define MOTOR_H

#include <ESP32Servo.h>

class Motor {
public:
    Motor();
    void begin(int pin);
    void update();
    void setHeartRate(int rate);
    float getHeartRate() const; 

private:
    Servo myServo;
    int heart_rate;
    int servo_start_angle;
    int servo_rotate_angle;
    float servo_rotate_time;
    
    // 快取變數
    float cachedWaitTime;
    float cachedMoveTime;
    float lastHeartRate;
    
    // 常量定義
    static const unsigned long UPDATE_INTERVAL = 20;  // 更新間隔（毫秒）
    
    // 私有方法
    void updateTimings();

    // 非阻塞控制變數
    unsigned long servoMoveStartTime;
    unsigned long cycleStartTime;
    int currentPosition;
    unsigned long lastUpdateTime;
    
    // 伺服馬達狀態列舉
    enum ServoState {
        MOVING_UP,    // 向上移動
        MOVING_DOWN,  // 向下移動
        WAITING      // 等待下一個週期
    };
    ServoState servoState;
};

#endif