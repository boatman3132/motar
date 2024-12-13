#include <Arduino.h>
#include <Stepper.h>

// 定義步進馬達的步數
const int stepsPerRevolution = 2048; // 28BYJ-48 的步數

// 初始化 Stepper 物件
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int stepsToMove = 0;


int heart_rate = 60; //RPM



void setup() {
  // 初始化串列通訊，設定波特率為9600
  Serial.begin(9600);
  // 設定馬達速度（每分鐘轉速）
  myStepper.setSpeed(1); // 5 RPM
}




void rotateMotor() {

  unsigned long currentMillis = millis();



// 心跳
  if (currentMillis % (60000/heart_rate) >= 0 && currentMillis % (60000/heart_rate) <= 200) {
    // 讓馬達正向旋轉一定的步數
    stepsToMove += 1; // 計算要移動的步數
    
  }

  if (currentMillis % (60000/heart_rate) >= (60000/heart_rate - 200) ) {
    // 讓馬達正向旋轉一定的步數
    stepsToMove -= 1; // 計算要移動的步數
    
  }




// 呼吸

  //   if (currentMillis % 6000 >= 0 && currentMillis % 6000 <= 1000) {
  //   // 讓馬達正向旋轉一定的步數
  //   stepsToMove += 1; // 計算要移動的步數
    
  // }

  // if (currentMillis % 6000 >= 2500 && currentMillis % 6000 <= 3500) {
  //   // 讓馬達正向旋轉一定的步數
  //   stepsToMove += -1; // 計算要移動的步數
    
  // }

  myStepper.step(stepsToMove);
  stepsToMove = 0;
}


void loop() {
  rotateMotor();
  Serial.print("Current execution time: ");
  Serial.println(millis());
}