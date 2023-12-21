#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "definitions.h"
#include "motor.h"

uint32_t Current_Time = 0;
uint32_t Previous_Time = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configure(void);
void ADC_Configure(void);
void USART1_Init(void);
void NVIC_Configuration(void);
void PWM_Configuration(void);
void ADC1_2_IRQHandler(void);
void TIM2_IRQHandler(void);
