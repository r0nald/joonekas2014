/**
  ******************************************************************************
  * @file    util.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    08-July-2013
  * @brief   This file contains definitions for Buttons control functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UTIL_H
#define __UTIL_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/* Exported macros -----------------------------------------------------------*/
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define SWAP(type, i, j) { type t = i; i = j; j = t; }
#define COUNT_OF(array) (sizeof(array) / sizeof(array[0]))
#define EI __enable_irq
#define DI __disable_irq

/* Exported functions ------------------------------------------------------- */
extern bool Util_Countdown(uint32_t * Timer, uint32_t Period, bool DetectEdge);
extern bool Util_ParseUInt32(const char * str, uint16_t length, bool ishex, uint32_t * value);
extern bool Util_ParseUInt16(const char * str, uint16_t length, bool ishex, uint16_t * value);
extern bool Util_ParseUInt8(const char * str, uint16_t length, bool ishex, uint8_t * value);
extern bool Util_ParseDouble(const char * str, uint16_t length, double * value);
extern bool Util_ParseGPSCoordinate(const char * str, uint16_t length, double * value);

#ifdef __cplusplus
}
#endif

#endif
