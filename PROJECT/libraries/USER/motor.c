#include "motor.h"

#include "definitions.h"

int isFroward = 0;
int isRotate = 0;

void delay() {
  int i;
  for (i = 0; i < 10000; i++)
    ;
}

// 왼쪽 모터 전진시키는 함수
void LEFT_MOTOR_FORWARD(void) {
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
  GPIO_SetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
}

// 왼쪽 모터 후진시키는 함수
void LEFT_MOTOR_BACKWARD(void) {
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
  GPIO_SetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
}

// 왼쪽 모터 멈추는 함수
void LEFT_MOTOR_STOP(void) {
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
}

// 오른쪽 모터 전진시키는 함수
void RIGHT_MOTOR_FORWARD(void) {
  GPIO_SetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
}

// 오른쪽 모터 후진시키는 함수
void RIGHT_MOTOR_BACKWARD(void) {
  GPIO_SetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
}

// 오른쪽 모터 멈추는 함수
void RIGHT_MOTOR_STOP(void) {
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
}

// 두 모터 전진시키는 함수
void FORWARD(void) {
  LEFT_MOTOR_FORWARD();
  RIGHT_MOTOR_FORWARD();
}

// 두 모터 후진시키는 함수
void BACKWARD(void) {
  LEFT_MOTOR_BACKWARD();
  RIGHT_MOTOR_BACKWARD();
}

// 두 모터 멈추는 함수
void STOP(void) {
  LEFT_MOTOR_STOP();
  RIGHT_MOTOR_STOP();
}

// 두 모터 시계방향으로 회전시키는 함수
void CLOCKWISE_ROTATION(void) {
  LEFT_MOTOR_BACKWARD();
  RIGHT_MOTOR_FORWARD();
}

// 두 모터 반시계방향으로 회전시키는 함수
void COUNTER_CLOCKWISE_ROTATION(void) {
  LEFT_MOTOR_FORWARD();
  RIGHT_MOTOR_BACKWARD();
}

// 두 모터를 one tick만큼 전진시키는 함수
void ONE_TICK_FORWARD(void) {
  TIM_SetCounter(TIM4, ONE_TICK);
  FORWARD();
}

// 두 모터를 one tick만큼 시계방향으로 회전시키는 함수
void ONE_TICK_CLOCKWISE_ROTATION(void) {
  
  TIM_SetCounter(TIM2, ONE_TICK);
  CLOCKWISE_ROTATION();
}

// 두 모터를 one tick만큼 반시계방향으로 회전시키는 함수
void ONE_TICK_COUNTER_CLOCKWISE_ROTATION(void) {
  TIM_SetCounter(TIM2, ONE_TICK);
  COUNTER_CLOCKWISE_ROTATION();
}