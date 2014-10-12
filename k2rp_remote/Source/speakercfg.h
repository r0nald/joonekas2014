/**
  ******************************************************************************
  * @file    speakercfg.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    28-June-2013
  * @brief   This file contains definitions for Speaker configuration.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPEAKERCFG_H
#define __SPEAKERCFG_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/* Public macro --------------------------------------------------------------*/
#define SPEAKER_TIMER           TIM3
#define SPEAKER_TIMER_CLK       RCC_APB1Periph_TIM3
#define SPEAKER_PIN             GPIO_Pin_0
#define SPEAKER_GPIO_PORT       GPIOB
#define SPEAKER_GPIO_CLK        RCC_AHB1Periph_GPIOB
#define SPEAKER_SOURCE          GPIO_PinSource0
#define SPEAKER_AF              GPIO_AF_TIM3
#define SPEAKER_MAIN_FREQUENCY  400000 /* In hertz */

#ifdef __cplusplus
}
#endif

#endif
