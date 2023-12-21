#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include "configuration.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

#define GPIO_Motor_In1_Pin GPIO_Pin_2
#define GPIO_Motor_In2_Pin GPIO_Pin_3
#define GPIO_Motor_In3_Pin GPIO_Pin_4
#define GPIO_Motor_In4_Pin GPIO_Pin_5

#define GPIO_Left_Motor_Port GPIOE
#define GPIO_Right_Motor_Port GPIOE

#define GPIO_Prox_Front_Port1 GPIOE
#define GPIO_Prox_Front_Port2 GPIOE
#define GPIO_Prox_Right_Port1 GPIOE
#define GPIO_Prox_Right_Port2 GPIOE

#define GPIO_Illumination_Port GPIOD

#define GPIO_Prox_Front_Pin1 GPIO_Pin_8
#define GPIO_Prox_Front_Pin2 GPIO_Pin_9
#define GPIO_Prox_Right_Pin1 GPIO_Pin_10
#define GPIO_Prox_Right_Pin2 GPIO_Pin_11

#define GPIO_Illumination_Pin GPIO_Pin_2

#define GPIO_Prox_Front_PortSource1 GPIO_PortSourceGPIOE
#define GPIO_Prox_Front_PortSource2 GPIO_PortSourceGPIOE
#define GPIO_Prox_Right_PortSource1 GPIO_PortSourceGPIOE
#define GPIO_Prox_Right_PortSource2 GPIO_PortSourceGPIOE

#define GPIO_Illumination_PortSource GPIO_PortSourceGPIOD

#define GPIO_Prox_Front_PinSource1 GPIO_PinSource8
#define GPIO_Prox_Front_PinSource2 GPIO_PinSource9
#define GPIO_Prox_Right_PinSource1 GPIO_PinSource10
#define GPIO_Prox_Right_PinSource2 GPIO_PinSource11

#define GPIO_Illumination_PinSource GPIO_PinSource2

#define EXTI_Prox_Front_Line1 EXTI_Line8
#define EXTI_Prox_Front_Line2 EXTI_Line9
#define EXTI_Prox_Right_Line1 EXTI_Line10
#define EXTI_Prox_Right_Line2 EXTI_Line11

#define EXTI_Illumination_Line EXTI_Line2

#define EXTI_Prox_Front_IRQn EXTI9_5_IRQn
#define EXTI_Prox_Right_IRQn EXTI15_10_IRQn

#define EXTI_Illumination_IRQn EXTI2_IRQn

#define ONE_TICK 105 * 90

#define M_PI 3.1415

#endif