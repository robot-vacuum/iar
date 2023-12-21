#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "definitions.h"
#include "motor.h"
#include "map.h"
#include "motor.h"
#include "move.h"

extern int isInturrupted;
extern int isClockWise;

extern uint32_t Current_Time;
extern uint32_t Previous_Time;

extern uint16_t Right_Interrupt_Status;

extern void Right_Interrupt_Enable(void);
extern void Right_Interrupt_Disable(void);

extern void RCC_Configuration(void);
extern void GPIO_Configuration(void);
extern void EXTI_Configure(void);
extern void ADC_Configure(void);
extern void USART12_Init(void);
extern void NVIC_Configuration(void);
extern void PWM_Configuration(void);
extern void ADC1_2_IRQHandler(void);
extern void TIM2_IRQHandler(void);
extern void TIM4_IRQHandler(void);

#endif
