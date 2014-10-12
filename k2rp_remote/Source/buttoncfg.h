/**
  ******************************************************************************
  * @file    buttoncfg.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    10-June-2013
  * @brief   This file contains definitions for Buttons configuration.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTONCFG_H
#define __BUTTONCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"
   
/* Public macro --------------------------------------------------------------*/
   
/* General */
#define BUTTON_COUNT              4
#define ACTIVE_MASK               0x0F

/* Pins */   
#define BUTTON_START_PIN          GPIO_Pin_4
#define BUTTON_START_GPIO_PORT    GPIOC
#define BUTTON_START_GPIO_CLK     RCC_AHB1Periph_GPIOC
#define BUTTON_START_EXTI_LINE    EXTI_Line4  
#define BUTTON_START_EXTI_IRQn    EXTI4_IRQn   
   
#define BUTTON_STOP_PIN           GPIO_Pin_10
#define BUTTON_STOP_GPIO_PORT     GPIOB
#define BUTTON_STOP_GPIO_CLK      RCC_AHB1Periph_GPIOB
   
#define BUTTON_LEFT_PIN           GPIO_Pin_2
#define BUTTON_LEFT_GPIO_PORT     GPIOB
#define BUTTON_LEFT_GPIO_CLK      RCC_AHB1Periph_GPIOB
   
#define BUTTON_RIGHT_PIN          GPIO_Pin_5
#define BUTTON_RIGHT_GPIO_PORT    GPIOC
#define BUTTON_RIGHt_GPIO_CLK     RCC_AHB1Periph_GPIOC

#ifdef __cplusplus
}
#endif

#endif
