/**
  ******************************************************************************
  * @file    logic.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    18-August-2013
  * @brief   This file contains definitions for Buttons control functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOGIC_H
#define __LOGIC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"   
   
/* Exported types ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void Logic_Init(void);
extern void Logic_Task(uint32_t Period);

#ifdef __cplusplus
}
#endif

#endif
