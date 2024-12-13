#include <Arduino.h>
#include <Stepper.h>

// 定義步進馬達的步數
const int stepsPerRevolution = 2048; // 28BYJ-48 的步數

// 初始化 Stepper 物件
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int stepsToMove = 0;

void setup() {
  // 初始化串列通訊，設定波特率為9600
  Serial.begin(9600);
  // 設定馬達速度（每分鐘轉速）
  myStepper.setSpeed(5); // 5 RPM
}


void rotateMotor() {

  unsigned long currentMillis = millis();

  if (currentMillis % 1000 >= 0 && currentMillis % 1000 <= 100) {
    // 讓馬達正向旋轉一定的步數
    stepsToMove += stepsPerRevolution * 0.002; // 計算要移動的步數
    
  }

  if (currentMillis % 1000 >= 800 && currentMillis % 1000 <= 900) {
    // 讓馬達正向旋轉一定的步數
    stepsToMove += -stepsPerRevolution * 0.002; // 計算要移動的步數
    
  }

    if (currentMillis % 5000 >= 0 && currentMillis % 5000 <= 2000) {
    // 讓馬達正向旋轉一定的步數
    stepsToMove += 1; // 計算要移動的步數
    
  }

  if (currentMillis % 5000 >= 2500 && currentMillis % 5000 <= 4500) {
    // 讓馬達正向旋轉一定的步數
    stepsToMove += -1; // 計算要移動的步數
    
  }

  myStepper.step(stepsToMove);
  stepsToMove = 0;
}


void loop() {
  rotateMotor();
  Serial.print("Current execution time: ");
  Serial.println(millis());
}