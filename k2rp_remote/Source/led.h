/**
  ******************************************************************************
  * @file    led.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    10-June-2012
  * @brief   This file contains definitions for LED control functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/* Exported functions ------------------------------------------------------- */
extern void LED_Init(void);
extern void LED_Task(uint32_t Period);
extern void LED_Set(void);
extern void LED_Clear(void);

#ifdef __cplusplus
}
#endif

#endif
