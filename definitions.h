#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

#include "configuration.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

#define GPIO_Motor_In1_Pin GPIO_Pin_2
#define GPIO_Motor_In2_Pin GPIO_Pin_3
#define GPIO_Motor_In3_Pin GPIO_Pin_4
#define GPIO_Motor_In4_Pin GPIO_Pin_5

#define GPIO_Left_Motor_Port GPIOE
#define GPIO_Right_Motor_Port GPIOE

#define GPIO_Prox_Left_Port GPIOC
#define GPIO_Prox_Front_Port GPIOC
#define GPIO_Prox_Right_Port GPIOC

#define GPIO_Prox_Left_Pin GPIO_Pin_2
#define GPIO_Prox_Front_Pin GPIO_Pin_3
#define GPIO_Prox_Right_Pin GPIO_Pin_4

#define GPIO_Prox_Left_PortSource GPIO_PortSourceGPIOC
#define GPIO_Prox_Front_PortSource GPIO_PortSourceGPIOC
#define GPIO_Prox_Right_PortSource GPIO_PortSourceGPIOC

#define GPIO_Prox_Left_PinSource GPIO_PinSource2
#define GPIO_Prox_Front_PinSource GPIO_PinSource3
#define GPIO_Prox_Right_PinSource GPIO_PinSource4

#define EXTI_Prox_Left_Line EXTI_Line2
#define EXTI_Prox_Front_Line EXTI_Line3
#define EXTI_Prox_Right_Line EXTI_Line4

#define EXTI_Prox_Left_IRQn EXTI2_IRQn
#define EXTI_Prox_Front_IRQn EXTI3_IRQn
#define EXTI_Prox_Right_IRQn EXTI4_IRQn


#define ONE_TICK 50000

#endif