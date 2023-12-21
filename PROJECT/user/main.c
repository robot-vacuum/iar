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
#include "configuration.h"
#include "definitions.h"
#include "map.h"
#include "motor.h"
#include "move.h"
#include <math.h>

int isDark = 0;

void circulateTargetMap()
{
  
  generalMove();
}

void updateTargetMap()
{
  assignConvexHull(source_Map, &source_Map_size);
  calcAndStoreMidPoints(source_Map, target_Map, &source_Map_size, &target_Map_size);
}

void sendTargetMap()
{
  USART_SendData(USART2, target_Map_size);

  for(int i = 0; i < target_Map_size; i++)
  {
    USART_SendData(USART2, target_Map[i].x);
    USART_SendData(USART2, target_Map[i].y);
  }
}

void setNextPoint()
{
  global_Next_Point = target_Map[target_Map_Idx++];
}

int main(void)
{
    RCC_Configuration();
    GPIO_Configuration();
    EXTI_Configure();
    USART12_Init();
    NVIC_Configuration();
    PWM_Configuration();
    
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    
    Point current_Loc = {0, 0};
    
    //initMap(source_Map, &source_Map_size, &source_Map_Idx);
    
    //ONE_TICK_FORWARD();
    
    //FORWARD();
 

    ONE_TICK_CLOCKWISE_ROTATION();
    
    while(1)
    {
      /*
      if(isDark == 0) continue;

      EXTI_LineCmd(EXTI_Illumination_Line, DISABLE);

      initMap(source_Map, &source_Map_size, &source_Map_Idx);
      initMap(target_Map, &target_Map_size, &target_Map_Idx);
      global_Theta = 0;
      global_Current_Point.x = 0; global_Current_Point.y = 0;

      while(target_Map_size > 2) 
      {
        circulateTargetMap();
        updateTargetMap();
        sendTargetMap();
      }

      isDark = 0;
      EXTI_LineCmd(EXTI_Illumination_Line, ENABLE);

      */
    }
}



