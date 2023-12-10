#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "definitions.h"

uint32_t Current_Time = 0;
uint32_t Previous_Time = 0;

double adc_value = 0;

// ********************************
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
    RIGHT_MOTOR_FORWARD();
}

void COUNTER_CLOCKWISE_RATATION(void)
{
    LEFT_MOTOR_BACKWARD();
    RIGHT_MOTOR_BACKWARD();
}
// ******************************

void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* motor driver setting */
    GPIO_InitStructure.GPIO_Pin = GPIO_Motor_In1_Pin | GPIO_Motor_In2_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIO_Left_Motor_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Motor_In3_Pin | GPIO_Motor_In4_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_Right_Motor_Port, &GPIO_InitStructure);

    // BTN Setting
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* USART1 pin setting */
    //TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   //RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU | GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* jodo sensor setting */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* 근접 센서 setting */
    GPIO_InitStructure.GPIO_Pin = /*GPIO_Prox_Left_Pin| */ GPIO_Prox_Front_Pin | GPIO_Prox_Right_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Prox_Front_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void EXTI_Configure(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    // GPIO_EXTILineConfig(GPIO_Prox_Left_PortSource, GPIO_Prox_Left_PinSource);
    // EXTI_InitStructure.EXTI_Line = EXTI_Prox_Left_Line;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_Prox_Front_PortSource, GPIO_Prox_Front_PinSource);
    EXTI_InitStructure.EXTI_Line = EXTI_Prox_Front_Line;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_Prox_Right_PortSource, GPIO_Prox_Right_PinSource);
    EXTI_InitStructure.EXTI_Line = EXTI_Prox_Right_Line;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void ADC_Configure()
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
   
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_239Cycles5);
    ADC_Init(ADC1, &ADC_InitStructure);
   
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
     
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void USART1_Init(void)
{
    USART_InitTypeDef USART1_InitStructure;
    USART_Cmd(USART1, ENABLE);
   
    USART1_InitStructure.USART_BaudRate = 9600;
    USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART1_InitStructure.USART_Parity = USART_Parity_No;
    USART1_InitStructure.USART_StopBits = USART_StopBits_1;
    USART1_InitStructure.USART_WordLength = USART_WordLength_8b;
   
    USART_Init(USART1, &USART1_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

    /* brightness sensor setting */
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Prox sensor setting */
    // NVIC_InitStructure.NVIC_IRQChannel = EXTI_Prox_Left_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    // NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI_Prox_Front_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI_Prox_Right_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

void PWM_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    uint16_t prescale = (uint16_t) (SystemCoreClock / 10000);
  
    TIM_TimeBaseStructure.TIM_Period = ONE_TICK;
    TIM_TimeBaseStructure.TIM_Prescaler = prescale;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
/*
    TIM_TimeBaseStructure.TIM_Period = 20000;
    TIM_TimeBaseStructure.TIM_Prescaler = prescale;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500; // us
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);*/
}

void ADC1_2_IRQHandler(void) 
{
    adc_value = (double)ADC_GetConversionValue(ADC1);
    ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        RIGHT_MOTOR_STOP();
            LEFT_MOTOR_STOP();

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

// void EXTI2_IRQHandler(void)
// {
//     if(EXTI_GetITStatus(EXTI_Prox_Left_Line) != RESET)
//     {
//         CLOCKWISE_ROTATION();

//         EXTI_ClearITPendingBit(EXTI_Prox_Left_Line);
//     }
// }

void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Prox_Front_Line) != RESET)
    {
        CLOCKWISE_ROTATION();

        EXTI_ClearITPendingBit(EXTI_Prox_Front_Line);
    }
}

void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Prox_Right_Line) != RESET)
    {
        LEFT_MOTOR_STOP();
        RIGHT_MOTOR_STOP();

        EXTI_ClearITPendingBit(EXTI_Prox_Right_Line);
    }
}

void USART2_IRQHandler() {
    uint16_t word;
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
        // the most recent received data by the USART2 peripheral
        word = USART_ReceiveData(USART2);

        switch (word - '0')
        {
        case 0:
          COUNTER_CLOCKWISE_RATATION();
          break;
        case 1:
          CLOCKWISE_ROTATION();
          break;
        
        default:
          break;
        }

        /*
        // TODO implement
        USART_SendData(USART1, word);
        */

        // clear 'Read data register not empty' flag
       USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }
}


void delay()
{
    int i;
    for(i = 0; i < 10000000; i++);
}

int main(void)
{
  SystemInit();
    RCC_Configuration();
    GPIO_Configuration();
    EXTI_Configure();
    NVIC_Configuration();
    PWM_Configuration();

    USART1_Init(); // bluetooth
    
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);


    while(1)
    {
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0)
        {
          
            CLOCKWISE_ROTATION();
            
        
        }
        delay();
    }
}
