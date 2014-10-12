/**
  ******************************************************************************
  * @file    speaker.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    28-June-2013
  * @brief   This file contains definitions for Speaker control functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPEAKER_H
#define __SPEAKER_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/* Exported functions ------------------------------------------------------- */
extern void Speaker_Init(void);
extern void Speaker_Task(uint32_t Period);
extern void Speaker_Beep(uint32_t Frequency, uint32_t Duration, uint8_t Volume);

#ifdef __cplusplus
}
#endif

#endif
