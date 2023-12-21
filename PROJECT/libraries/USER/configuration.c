#include "configuration.h"

int isInturrupted = 0;
int isClockWise = 0;

uint16_t Right_Interrupt_Status;

EXTI_InitTypeDef EXTI_InitStructure;

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;

void Right_Interrupt_Enable(void) {
  Right_Interrupt_Status = 1;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void Right_Interrupt_Disable(void) {
  Right_Interrupt_Status = 0;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void RCC_Configuration(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
}

void GPIO_Configuration(void) {
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

  /* USART1 pin setting (USART1 Port)*/
  // TX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU | GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* USART2 pin setting (BLE)*/ 
  // TX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU | GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //     /* jodo sensor setting */
  GPIO_InitStructure.GPIO_Pin = GPIO_Illumination_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_Illumination_Port, &GPIO_InitStructure);

  /* 근접 센서 setting */
  GPIO_InitStructure.GPIO_Pin = GPIO_Prox_Front_Pin1 | GPIO_Prox_Front_Pin2 |
                                GPIO_Prox_Right_Pin1 | GPIO_Prox_Right_Pin2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_Prox_Front_Port1, &GPIO_InitStructure);

  /*
  GPIO_InitStructure.GPIO_Pin = GPIO_Prox_Front_Pin | GPIO_Prox_Right_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);*/

  // Debuggin LED
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void EXTI_Configure(void) {
  GPIO_EXTILineConfig(GPIO_Prox_Front_PortSource1, GPIO_Prox_Front_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Prox_Front_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_Prox_Front_PortSource2, GPIO_Prox_Front_PinSource2);
  EXTI_InitStructure.EXTI_Line = EXTI_Prox_Front_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_Prox_Right_PortSource1, GPIO_Prox_Right_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Prox_Right_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_Prox_Right_PortSource2, GPIO_Prox_Right_PinSource2);
  EXTI_InitStructure.EXTI_Line = EXTI_Prox_Right_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_Illumination_PortSource,
                      GPIO_Illumination_PinSource);
  EXTI_InitStructure.EXTI_Line = EXTI_Illumination_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  Right_Interrupt_Status = 0;
}

void USART12_Init(void) {
  USART_InitTypeDef USART1_InitStructure;
  USART_InitTypeDef USART2_InitStructure;
  USART_Cmd(USART1, ENABLE);

  USART1_InitStructure.USART_BaudRate = 9600;
  USART1_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;
  USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART1_InitStructure.USART_Parity = USART_Parity_No;
  USART1_InitStructure.USART_StopBits = USART_StopBits_1;
  USART1_InitStructure.USART_WordLength = USART_WordLength_8b;

  USART_Init(USART1, &USART1_InitStructure);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  USART_Cmd(USART2, ENABLE);

  USART2_InitStructure.USART_BaudRate = 9600;
  USART2_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;
  USART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART2_InitStructure.USART_Parity = USART_Parity_No;
  USART2_InitStructure.USART_StopBits = USART_StopBits_1;
  USART2_InitStructure.USART_WordLength = USART_WordLength_8b;

  USART_Init(USART2, &USART2_InitStructure);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void NVIC_Configuration(void) {
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  // Timer for Rotating
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  // Timer for Forwarding
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);

  /* Prox sensor setting */

  NVIC_InitStructure.NVIC_IRQChannel = EXTI_Prox_Front_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI_Prox_Right_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI_Illumination_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);
}

void PWM_Configuration(void) {
  uint16_t prescale = (uint16_t)(SystemCoreClock / 10000);

  TIM_TimeBaseStructure.TIM_Period = ONE_TICK;
  TIM_TimeBaseStructure.TIM_Prescaler = prescale;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = ONE_TICK;
  TIM_TimeBaseStructure.TIM_Prescaler = prescale;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = 20000;
  TIM_TimeBaseStructure.TIM_Prescaler = prescale;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1500;  // us
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
}

// Front Prox IRQHandler
void EXTI9_5_IRQHandler(void) {
  if (EXTI_GetITStatus(EXTI_Prox_Front_Line1) != RESET ||
      EXTI_GetITStatus(EXTI_Prox_Front_Line2) != RESET) {
    STOP();
    TIM_Cmd(TIM2, DISABLE);

    isClockWise = 0;
    while (GPIO_ReadInputDataBit(GPIO_Prox_Front_Port1, GPIO_Prox_Front_Pin1) ==
               0 &&
           GPIO_ReadInputDataBit(GPIO_Prox_Front_Port2, GPIO_Prox_Front_Pin2) ==
               0) {
      ONE_TICK_COUNTER_CLOCKWISE_ROTATION();
    }

    /*
            EXTI_LineCmd(EXTI_Prox_Right_Line1, ENABLE);
            EXTI_LineCmd(EXTI_Prox_Right_Line2, ENABLE);
    */

    isInturrupted = 1;
    EXTI_ClearITPendingBit(EXTI_Prox_Front_Line1);
    EXTI_ClearITPendingBit(EXTI_Prox_Front_Line2);
  }
}

// Right Prox IRQHandler
void EXTI15_10_IRQHandler(void) {
  if (EXTI_GetITStatus(EXTI_Prox_Right_Line1) != RESET ||
      EXTI_GetITStatus(EXTI_Prox_Right_Line2) != RESET) {
    STOP();
    TIM_Cmd(TIM2, DISABLE);

    isClockWise = 1;
    while (GPIO_ReadInputDataBit(GPIO_Prox_Right_Port1, GPIO_Prox_Right_Pin1) ==
               1 &&
           GPIO_ReadInputDataBit(GPIO_Prox_Right_Port2, GPIO_Prox_Right_Pin2) ==
               1) {
      ONE_TICK_CLOCKWISE_ROTATION();
    }

    EXTI_ClearITPendingBit(EXTI_Prox_Right_Line2);
    EXTI_ClearITPendingBit(EXTI_Prox_Right_Line1);
  }
}

// Illumination IRQHandler
void EXTI2_IRQHandler(void) {
  if (EXTI_GetITStatus(EXTI_Illumination_Line) != RESET) {
    GPIO_EXTILineConfig(GPIO_Prox_Front_PortSource1, GPIO_Prox_Front_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Prox_Front_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_Prox_Front_PortSource2, GPIO_Prox_Front_PinSource2);
    EXTI_InitStructure.EXTI_Line = EXTI_Prox_Front_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_Illumination_PortSource,
                      GPIO_Illumination_PinSource);
  EXTI_InitStructure.EXTI_Line = EXTI_Illumination_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);
    
    
    EXTI_ClearITPendingBit(EXTI_Illumination_Line);
  }
}

// Rotation Timer
void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    STOP();
    global_Theta = (global_Theta + 1 * (isClockWise ? -1 : 1) + 360) % 360;

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

// Forwarding Timer
void TIM4_IRQHandler(void) {
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
    STOP();
    global_Current_Point.x += FORWARD_TICK * cosf(thetaToRad(global_Theta));
    global_Current_Point.y += FORWARD_TICK * sinf(thetaToRad(global_Theta));

    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  }
}

void USART1_IRQHandler() {
  uint16_t word;
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    // the most recent received data by the USART2 peripheral
    word = USART_ReceiveData(USART1);

    USART_SendData(USART2, word);

    // clear 'Read data register not empty' flag
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
}

void USART2_IRQHandler() {
  uint16_t word;
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
    // the most recent received data by the USART2 peripheral
    word = USART_ReceiveData(USART2);

    switch (word - '0') {
      case 0:
        COUNTER_CLOCKWISE_ROTATION();
        break;
      case 1:
        CLOCKWISE_ROTATION();
        break;

      default:
        break;
    }

    USART_SendData(USART1, word);

    // clear 'Read data register not empty' flag
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
}
