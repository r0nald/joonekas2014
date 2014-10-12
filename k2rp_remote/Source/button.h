/**
  ******************************************************************************
  * @file    button.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    28-June-2013
  * @brief   This file contains definitions for Buttons control functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"   
   
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  Button_Start,
  Button_Stop,
  Button_Left,
  Button_Right  
}
Button_TypeDef;

/* Exported functions ------------------------------------------------------- */
extern void Button_Init(void);
extern void Button_Task(uint32_t Period);
extern bool Button_IsDown(Button_TypeDef Button);
extern bool Button_IsPressed(Button_TypeDef Button);
extern bool Button_IsReleased(Button_TypeDef Button);

#ifdef __cplusplus
}
#endif

#endif
