#include "motor.h"
#include "definitions.h"

void delay() {
  int i;
  for (i = 0; i < 10000; i++)
    ;
}

void LEFT_MOTOR_FORWARD(void) {
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
  GPIO_SetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
}

void LEFT_MOTOR_BACKWARD(void) {
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
  GPIO_SetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
}

void LEFT_MOTOR_STOP(void) {
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
  GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
}

void RIGHT_MOTOR_FORWARD(void) {
  GPIO_SetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
}

void RIGHT_MOTOR_BACKWARD(void) {
  GPIO_SetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
}

void RIGHT_MOTOR_STOP(void) {
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
  GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
}

void FORWARD(void) {
  LEFT_MOTOR_FORWARD();
  RIGHT_MOTOR_FORWARD();
}

void BACKWARD(void) {
  LEFT_MOTOR_BACKWARD();
  RIGHT_MOTOR_BACKWARD();
}

void STOP(void) {
  LEFT_MOTOR_STOP();
  RIGHT_MOTOR_STOP();
}

void CLOCKWISE_ROTATION(void) {
  LEFT_MOTOR_BACKWARD();
  RIGHT_MOTOR_FORWARD();
}

void COUNTER_CLOCKWISE_ROTATION(void) {
  LEFT_MOTOR_FORWARD();
  RIGHT_MOTOR_BACKWARD();
}

void ONE_TICK_FORWARD(void) {
  TIM_SetCounter(TIM4, ONE_TICK);
  FORWARD();
}

void ONE_TICK_CLOCKWISE_ROTATION(void) {
  TIM_SetCounter(TIM2, ONE_TICK);
  isClockWise = 1;
  CLOCKWISE_ROTATION();
}

void ONE_TICK_COUNTER_CLOCKWISE_ROTATION(void) {
  TIM_SetCounter(TIM2, ONE_TICK);
  isClockWise = 0;
  COUNTER_CLOCKWISE_ROTATION();
}