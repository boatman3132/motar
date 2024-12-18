#include <Arduino.h>
#include "motor.h"
#include "UARTHandler.h"

UARTHandler uartHandler;
Motor motor;

float currentHeartRateBPM = 0.0;
float currentBreathingRateRPM = 0.0;

void setup() {
    Serial.begin(9600);
    motor.begin(1);  // 使用 GPIO 1
    uartHandler.begin();
}

void loop() {
    static unsigned long lastMotorUpdate = 0;
    static unsigned long lastReadTime = 0;
    unsigned long currentTime = millis();
    
    // 降低馬達更新頻率
    if (currentTime - lastMotorUpdate >= 20) {
        lastMotorUpdate = currentTime;
        motor.update();
    }

    // 降低UART讀取頻率
    if (currentTime - lastReadTime >= 200) {
        lastReadTime = currentTime;
        
        if (uartHandler.readData()) {
            RadarData radarData = uartHandler.getRadarData();
            currentHeartRateBPM = radarData.heartRateEst;
            currentBreathingRateRPM = radarData.breathingRateEst;
            
            // 降低Serial輸出頻率
            static unsigned long lastPrintTime = 0;
            if (currentTime - lastPrintTime >= 1000) {  // 每秒只輸出一次
                lastPrintTime = currentTime;
                Serial.print("模擬心率: ");
                Serial.print(motor.getHeartRate());
                Serial.print("  心跳率: ");
                Serial.print(currentHeartRateBPM);
                Serial.print("  呼吸率: ");
                Serial.println(currentBreathingRateRPM);
            }
        }
    }
}