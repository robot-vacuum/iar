#include "motor.h"
#include "definitions.h"

void LEFT_MOTOR_FORWARD(void)
{
    GPIO_SetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
    GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
}

void LEFT_MOTOR_BACKWARD(void)
{
    GPIO_SetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
    GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
}

void LEFT_MOTOR_STOP(void)
{
    GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In1_Pin);
    GPIO_ResetBits(GPIO_Left_Motor_Port, GPIO_Motor_In2_Pin);
}

void RIGHT_MOTOR_FORWARD(void)
{
    GPIO_SetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
    GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);  
}

void RIGHT_MOTOR_BACKWARD(void)
{
    GPIO_SetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
    GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
}

void RIGHT_MOTOR_STOP(void)
{
    GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In3_Pin);
    GPIO_ResetBits(GPIO_Right_Motor_Port, GPIO_Motor_In4_Pin);
}

void FORWARD(void)
{
    LEFT_MOTOR_FORWARD();
    RIGHT_MOTOR_FORWARD();
}

void BACKWARD(void)
{
    LEFT_MOTOR_BACKWARD();
    RIGHT_MOTOR_BACKWARD();
}

void CLOCKWISE_ROTATION(void)
{
    LEFT_MOTOR_FORWARD();
    RIGHT_MOTOR_BACKWARD();
}

void COUNTER_CLOCKWISE_RATATION(void)
{
    LEFT_MOTOR_BACKWARD();
    RIGHT_MOTOR_FORWARD();
}