#include <math.h>

#include "stm32f10x.h"
#include "configuration.h"
#include "core_cm3.h"
#include "definitions.h"
#include "lcd.h"
#include "map.h"
#include "misc.h"
#include "motor.h"
#include "move.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "touch.h"


// 블루투스 master host 에게 target map의 좌표를 전송하는 함수
void sendTargetMap() {
  char words[100];
  int size = 0;
  
  USART_SendData(USART2, (uint16_t)'S');
  USARTDelay();
  integerToString(words, target_Map_size, &size);
  sendWords(words, size);

  for (int i = 0; i < target_Map_size; i++) {
    integerToString(words, (uint32_t)(target_Map[i].x * 1000), &size);
    sendWords(words, size);
    integerToString(words, (uint32_t)(target_Map[i].y * 1000), &size);
    sendWords(words, size);
  }
}

// 비동기 방식의 USART 동기화를 위한 명시적 delay
void USARTDelay() {
  uint32_t i;
  for (i = 0; i < 1000000; i++)
    ;
}

void circulateTargetMap() { generalMove(); }

// inetger를 string으로 변환해주는 함수
void integerToString(char *words, uint32_t num, int *size)
{
  int i = 0;
  if(num == 0) {
    words[i++] = '0';
  } else {
    while(num > 0) {
      words[i++] = (char)(num % 10 + '0');
      num /= 10;
    }
  }
  
  *size = i;
}

// targetMap update 함수
void updateTargetMap() {
  assignConvexHull(source_Map, &source_Map_size);
  calcAndStoreMidPoints(source_Map, target_Map, &source_Map_size, &target_Map_size);
}

// 블루투스를 통해 string을 전송하는 함수
void sendWords(char *words, int size)
{
  for(int i = 0; i < size; ++i) {
    USART_SendData(USART2, (uint16_t)words[i]);
    USARTDelay();
  }
  USART_SendData(USART2, (uint16_t)'\n');  
  USARTDelay();    
}

// 현재 위치를 USART를 통해 전송하는 함수
void sendCurrentPoint(Point current_Point)
{
  char words[100];
  int size = 0;

  USART_SendData(USART2, (uint16_t)'S');
  USARTDelay();

  integerToString(words, (uint32_t)(ceilf(current_Point.x) * 1000), &size);
  sendWords(words, size);
  integerToString(words, (uint32_t)(ceilf(current_Point.y) * 1000), &size);
  sendWords(words, size);
}

void setNextPoint() { global_Next_Point = target_Map[target_Map_Idx++]; }

int main(void) {
  RCC_Configuration();
  GPIO_Configuration();
  EXTI_Configure();
  USART12_Init();
  PWM_Configuration();
  NVIC_Configuration();


  while (1) {
    if(!isDark) continue;

    global_Theta = 0;
    global_Current_Point.x = 0; global_Current_Point.y = 0;


    while(1)
    {
      if(isRotate) continue;

      FORWARD();
      delay();
    
      if(inner_Map_Idx > 5) {
        while(inner_Map_Idx > 0) {
          sendCurrentPoint(inner_Map[--inner_Map_Idx]);
        }
      }
    }

    isDark = 0;
    EXTI_Cmd(EXTI_Illumination_Line, ENABLE);

  }
}
