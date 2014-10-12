/**
  ******************************************************************************
  * @file    power.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    08-July-2013
  * @brief   This file contains definitions for Power control functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __POWER_H
#define __POWER_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  Power_On,
  Power_Off
}
PowerStatus_TypeDef;

/* Exported functions ------------------------------------------------------- */
extern void Power_Init(void);
extern void Power_Task(uint32_t Period);
extern void Power_TurnOff(uint32_t Delay);
extern uint16_t Power_GetSupplyVoltage(void);
extern bool Power_IsBatteryCharging(void);
extern bool Power_Is_USB_Connected(void);
extern uint8_t Power_GetBatteryLevel(void);
extern uint16_t Power_GetTemperature(void);

#ifdef __cplusplus
}
#endif

#endif
