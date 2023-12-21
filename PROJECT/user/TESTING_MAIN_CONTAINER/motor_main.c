#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "lcd.h"
#include "touch.h"

#define ONE_TICK 100000

#define LEFT_MOTOR_PORT GPIOC
#define RIGHT_MOTOR_PORT GPIOC

#define LEFT_MOTOR_PIN_IN1 GPIO_Pin_0
#define LEFT_MOTOR_PIN_IN2 GPIO_Pin_1
#define RIGHT_MOTOR_PIN_IN1 GPIO_Pin_2
#define RIGHT_MOTOR_PIN_IN2 GPIO_Pin_3

void LEFT_MOTOR_FORWARD(void);
void LEFT_MOTOR_BACKWARD(void);
void LEFT_MOTOR_STOP(void);

void RIGHT_MOTOR_FORWARD(void);
void RIGHT_MOTOR_BACKWARD(void);
void RIGHT_MOTOR_STOP(void);

void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_PIN_IN1 | LEFT_MOTOR_PIN_IN2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LEFT_MOTOR_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_PIN_IN1 | RIGHT_MOTOR_PIN_IN2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RIGHT_MOTOR_PORT, &GPIO_InitStructure);

    // BTN Setting
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void PWM_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    uint16_t prescale = (uint16_t) (SystemCoreClock / 100000);
  
    TIM_TimeBaseStructure.TIM_Period = ONE_TICK * 360;
    TIM_TimeBaseStructure.TIM_Prescaler = prescale;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        LEFT_MOTOR_STOP();
        RIGHT_MOTOR_STOP();

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void delay()
{
    uint32_t i;
    for(i = 0; i < 1000000; i++);
}

int main(void)
{
    RCC_Configuration();
    GPIO_Configuration();
    NVIC_Configuration();
    PWM_Configuration();


    while(1)
    {
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0)
        {
            LEFT_MOTOR_FORWARD();
            RIGHT_MOTOR_BACKWARD();
        }
        delay();
    }
}

void LEFT_MOTOR_FORWARD(void)
{
    GPIO_SetBits(LEFT_MOTOR_PORT, LEFT_MOTOR_PIN_IN1);
    GPIO_ResetBits(LEFT_MOTOR_PORT, LEFT_MOTOR_PIN_IN2);
}

void LEFT_MOTOR_BACKWARD(void)
{
    GPIO_ResetBits(LEFT_MOTOR_PORT, LEFT_MOTOR_PIN_IN1);
    GPIO_SetBits(LEFT_MOTOR_PORT, LEFT_MOTOR_PIN_IN2);
}

void LEFT_MOTOR_STOP(void)
{
    GPIO_ResetBits(LEFT_MOTOR_PORT, LEFT_MOTOR_PIN_IN1);
    GPIO_ResetBits(LEFT_MOTOR_PORT, LEFT_MOTOR_PIN_IN2);
}

void RIGHT_MOTOR_FORWARD(void)
{
    GPIO_SetBits(RIGHT_MOTOR_PORT, RIGHT_MOTOR_PIN_IN1);
    GPIO_ResetBits(RIGHT_MOTOR_PORT, RIGHT_MOTOR_PIN_IN2);
}

void RIGHT_MOTOR_BACKWARD(void)
{
    GPIO_ResetBits(RIGHT_MOTOR_PORT, RIGHT_MOTOR_PIN_IN1);
    GPIO_SetBits(RIGHT_MOTOR_PORT, RIGHT_MOTOR_PIN_IN2);
}

void RIGHT_MOTOR_STOP(void)
{
    GPIO_ResetBits(RIGHT_MOTOR_PORT, RIGHT_MOTOR_PIN_IN1);
    GPIO_ResetBits(RIGHT_MOTOR_PORT, RIGHT_MOTOR_PIN_IN2);
}

