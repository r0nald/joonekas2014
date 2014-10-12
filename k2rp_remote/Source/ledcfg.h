/**
  ******************************************************************************
  * @file    ledcfg.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    10-June-2012
  * @brief   This file contains definitions for LED configuration.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LEDCFG_H
#define __LEDCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/* Public macro --------------------------------------------------------------*/
#define LED_PIN          GPIO_Pin_8
#define LED_GPIO_PORT    GPIOC
#define LED_GPIO_CLK     RCC_AHB1Periph_GPIOC

#ifdef __cplusplus
}
#endif

#endif
