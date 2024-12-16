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
    
private:
    Servo myServo;
    int heart_rate;
    int servo_start_angle;
    int servo_rotate_angle;
    float servo_rotate_time;
    unsigned long previousMillis;
    int seconds_elapsed;
    static const int interval = 10;
    static const int heart_rate_increase = 10;
    static const int seconds_elapsed_max = 100;
    int heart_rate_min;

    // 新增用於非阻塞控制的變數
    unsigned long servoMoveStartTime;  // 伺服馬達移動開始時間
    unsigned long cycleStartTime;      // 心跳週期開始時間
    int currentPosition;               // 目前伺服馬達位置
    
    // 伺服馬達狀態列舉
    enum ServoState {
        MOVING_UP,    // 向上移動
        MOVING_DOWN,  // 向下移動
        WAITING      // 等待下一個週期
    };
    ServoState servoState;  // 目前伺服馬達狀態
};

#endif